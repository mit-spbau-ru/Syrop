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
				try {
						FileInfo file ( fname );
						return ProxySettings ( file.getName() );
				}
				catch ( std::runtime_error const &e ) {
						throw ( e );
				}
				 
		}

        /**
         * @param dir
         */
		map< string, ProxySettings > readAllProxySettings ( string dir )
		{
<<<<<<< HEAD
				files_t  allFiles;
				filter_dir_files( dir, allFiles );
				files_t::const_iterator afit = allFiles.begin();
=======
		        if (dir.at(dir.size() - 1) != '/')
		            dir += "/";
		            
				vector < string > allFiles = list_dir_files( dir );
				vector < string >::const_iterator afit = allFiles.begin();
>>>>>>> 843fc3b5f4be1caad2de6aaeaea49eb97be86855

				map < string, ProxySettings > allSettings;
				for ( ; afit != allFiles.end(); ++afit )
				{
<<<<<<< HEAD
						allSettings.insert( make_pair ( afit->getName() , readProxySettings( afit->getName() )) );
=======
				// TODO :: catch exceptions here
						allSettings[fileToNet( *afit )].loadData( dir + *afit );
>>>>>>> 843fc3b5f4be1caad2de6aaeaea49eb97be86855
				}
				return allSettings;
		}

	template < class T >	
	void makeConfig(string const &fname, T const & configer )
	{
		try{ 
			FileInfo f(fname) ;
		
			std::ofstream file;
			
			std::vector < string > split_vec; 
			boost::split( split_vec, fname, boost::is_any_of("/") );
			string name = split_vec.back();
			string dir = f.getFullName();
			dir = dir.erase ( fname.find_last_of (name) ) ;
			create_dir( dir );
			file.open ( name.c_str() );
			
			configer.generate(file);

			file.close ();
		}
		catch ( std::runtime_error const &e ) {
					throw ( e );
		}

	}

} // namespace utils
