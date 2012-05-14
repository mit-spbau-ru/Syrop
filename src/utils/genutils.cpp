#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "genutils.h"
#include "system.h"
#include <sys/stat.h>

namespace utils{
		
    using std::string;
    using std::runtime_error;

    /**
     * checks if file with the specified name exists
     *
     * @param fname full name of the file
     *
     */
    bool fileExists( string const &fname )
    {   
        struct stat s;
        return ( stat( fname.c_str(), &s ) != -1 ); 
    }

    /**
     * 
     * loads all the files with settings given in 
     * a directory into map object
     *
     * @param dir full name of the directory
     * @param allSettings a map to store the loaded settings
     *
     */
    void readAllProxySettings ( string const & dir, 
                                map< string, ProxySettings > & allSettings )
    {
        files_t allFiles;
        string dirName = dir; 
        size_t res =  dirName.find("~"); 
        if ( res != std::string::npos )
        {
            dirName.erase ( res, 1 );
            dirName.insert( res, get_user_home_dir() );
        }

        filter_dir_files( dirName , allFiles ); 

        for ( files_t::const_iterator afit = allFiles.begin() ; afit != allFiles.end(); ++afit )
        {
            allSettings.insert( std::make_pair ( afit->getName()  , 
                                                ProxySettings( afit->getFullName() )) );
        }
    }

    /**
     *
     * returns the name of a net configured for a given name of file with settings
     *
     * @param full name of the file
     *
     */
    string netFromFileName( string const & name )
    {
        return FileInfo( name ).getName();        
    }
 
    /**
     *
     * returns the name of file with settings given a net name
     *
     * @param full name of the net
     *
     */
    string fileNameFromNet( string const & name )
    {
        return name;
    }

    /**
     *
     * given a full path of a file location returns the path of its parent directories
     *
     * @param fname full name of the file
     *
     */
    string parent ( string const & fname )
    {
        std::vector < string > split_vec; 
        boost::split( split_vec, fname, boost::is_any_of("/") );
        string name = split_vec.back();
        string dir = fname;
        return dir.erase ( fname.find_last_of (name) ) ;
	}
    
    /**
     *
     * template function that writes a configuration file
     * of the Syrop application
     *
     * @param fname full name of the file
     * @param configer a class object able to generate configuration
     */
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
