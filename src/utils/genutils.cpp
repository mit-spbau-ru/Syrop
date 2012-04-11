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

    void readAllProxySettings ( string const & dir, 
                                map< string, ProxySettings > & allSettings )
    {
        files_t allFiles;
        string dirName = dir; 
        size_t res =  dirName.find("~"); 
        if ( res != std::string::npos )
        {
            dirName.erase ( res, 1 );
            dirName.insert( res , user_home_dir() );
        }

        filter_dir_files( dirName , allFiles ); // usr home dir

        for ( files_t::const_iterator afit = allFiles.begin() ; afit != allFiles.end(); ++afit )
        {
            allSettings.insert( std::make_pair ( afit->getName()  , 
                                                ProxySettings( afit->getFullName() )) );
        }
    }

    string parent ( string const & fname )
    {
        std::vector < string > split_vec; 
        boost::split( split_vec, fname, boost::is_any_of("/") );
        string name = split_vec.back();
        string dir = fname;
        return dir.erase ( fname.find_last_of (name) ) ;
	}
    
    template < class T >	
    void makeConfig(string const &fname, T const & configer )
    {
        if (! fileExists(fname) )
        {	
            std::ofstream file;
			string p = parent( fname );
		   
            create_dir( p );
            file.open ( fname.c_str() );
			
            configer.generate(file);

            file.close ();
        }

    }
                                                                
} // namespace utils
