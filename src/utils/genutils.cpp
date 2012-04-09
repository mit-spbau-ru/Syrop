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

		ProxySettings readProxySettings( string const & fname )
		{
				FileInfo file ( fname );
				return ProxySettings ( file.getName() );
		}

		void readAllProxySettings ( string const & dir, map< string, ProxySettings > &allSettings )
		{
				files_t  allFiles;
				filter_dir_files( dir, allFiles );
				files_t::const_iterator afit = allFiles.begin();

				for ( ; afit != allFiles.end(); ++afit )
				{
						allSettings.insert( make_pair ( afit->getName() , readProxySettings( afit->getFullName() )) );
				}
		}

	template < class T >	
	void makeConfig(string const &fname, T const & configer )
	{
			FileInfo f(fname) ;
		
			std::ofstream file;
			
		    string name = f.getName();
			string dir = f.getFullName();
			dir = dir.erase ( fname.find_last_of (name) ) ;
			create_dir( dir );
			file.open ( name.c_str() );
			
			configer.generate(file);

			file.close ();

	}

} // namespace utils
