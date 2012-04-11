#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "genutils.h"
#include "system.h"


namespace utils{
		
    using std::string;
    using std::runtime_error;

    bool fileExists( string const &fname )
    {
        return std::ifstream( fname.c_str() ,  std::ifstream::in );
    }

    ProxySettings readProxySettings( string const & fname )
    {
        return ProxySettings ( fname );
    }

    void readAllProxySettings ( string const & dir, 
                                map< string, ProxySettings > & allSettings )
    {
        files_t allFiles; 
        filter_dir_files( FileInfo(dir).getFullName() , allFiles ); // usr home dir

        for ( files_t::const_iterator afit = allFiles.begin() ; afit != allFiles.end(); ++afit )
        {
            allSettings.insert( std::make_pair ( afit->getName()  , 
                                                ProxySettings( afit->getFullName() )) );
        }
    }

    pair < string, string > getParentAndFile ( string const & fname )
    {
        std::vector < string > split_vec; 
        boost::split( split_vec, fname, boost::is_any_of("/") );
        string name = split_vec.back();
        string dir = fname;
        return make_pair ( dir.erase ( fname.find_last_of (name) ), name ) ;
	}

    template < class T >	
    void makeConfig(string const &fname, T const & configer )
    {
        if (! fileExists(fname) )
        {	
            std::ofstream file;
			pair < string, string > p = getParentAndFile( fname );
		   
            create_dir( p.first );
            file.open ( p.second.c_str() );
			
            configer.generate(file);

            file.close ();
        }

    }
                                                                
} // namespace utils
