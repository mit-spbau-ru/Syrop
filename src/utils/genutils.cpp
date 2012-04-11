#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "genutils.h"
#include "proxysettings.h"
#include "system.h"


namespace utils{
		
	using std::string;
    using std::runtime_error;

	bool fileExists( string const &fname )
	{
	  return std::ifstream( fname.c_str() ,  std::ifstream::in ) != NULL;
	}

	string fileToNet( string const & fname )
	{
		std::vector < string > split_vec; 
		boost::split( split_vec, fname, boost::is_any_of(".") );
		return split_vec.front();				
	}	

	string netToFile( string const & fname )
	{	
		return fname + ".ini";						
	}

	ProxySettings readProxySettings( string const & fname )
	{
		return ProxySettings ( fname );
	}

	map< string, ProxySettings > readAllProxySettings ( string const & dir)
	{
		vector < string > allFiles; 
        filter_dir_files( dir, allFiles );
		vector < string >::const_iterator afit = allFiles.begin();

		map < string, ProxySettings > allSettings;
		for ( ; afit != allFiles.end(); ++afit )
		{
			allSettings.insert( make_pair ( fileToNet( *afit ) , ProxySettings( *afit )) );
		}
	return allSettings;
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
