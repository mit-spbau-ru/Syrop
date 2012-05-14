#include <fstream>
#include <stdexcept>
#include "proxysettings.h"
#include "genutils.h"

namespace utils{

    /**
     *
     * checks existence of an application in the class object
     * 
     * @param appName name of the application
     *
     */
    bool ProxySettings::existsApp( string const &appName ) const
    {
        return data.hasSection ( appName ) ;
    }		
    
    /**
     *
     * removes a specified application from the data object stored in the class
     * 
     * @param appName name of the application to remove
     * @throws std::runtime_error if there is no such in application stored
     *
     */
	void ProxySettings::removeApp( string const &appName )
	{
		if ( !data.hasSection ( appName ) )
			throw std::runtime_error( "there is no \"" + appName + "\" application to erase" );
		data.removeSection( appName ) ;
	}		
	
	/**
	 * first call existsApp() is suggested to check if such an item exists in the map
     *
     * @param appName name of the application 
     *
	 */
	attributes const & ProxySettings::operator[] (string const &appName) const
	{
		static const attributes attrs;
		if ( ! existsApp(appName) )
		{
			if ( existsApp( "default" ) )  return data[ "default" ];
			else return attrs;
		}
		return data [ appName ];
	}

 	/**
	 * first call existsApp() is suggested to check if such an item exists in the map
     *
     * @param appName name of the application 
     *
	 */
	attributes & ProxySettings::operator[] (string const &appName) 
	{
		static attributes attrs;
		if ( ! existsApp(appName) )
		{
			if ( existsApp( "default" ) )  return data[ "default" ];
			else return attrs;
		}
		return data [ appName ];
	}
    
     /**
	 * returns a const iterator to the beginning of the data stored
	 */
	ProxySettings::const_iterator  ProxySettings::begin () const
	{
		 return data.begin();
	}

	/**
	 * returns a const iterator to the end of the data stored
	 */
	ProxySettings::const_iterator  ProxySettings::end () const
	{
		 return data.end();
	}

	/**
	 * returns an iterator to the beginning of the data stored
	 */
	ProxySettings::iterator  ProxySettings::begin ()
	{
		return data.begin();
	}

	/**
	 * returns an iterator to the end of the data stored
	 */
	ProxySettings::iterator  ProxySettings::end ()
	{
		return data.end();
	}


	/**
	 * get a file name and if the file exists write data settings
	 * in it
     *
     * @param fileName name of the file to save in
     * @throws std::runtime_error if problems with I/O occur
     *
	 */
	void ProxySettings::save( string const &fileName  ) const
	{
		std::ofstream file(fileName.c_str());
		if (!file)
			throw std::runtime_error("Can't open \"" + fileName + "\" for writing");	
        file << data;	
	}

	/**
	 * get a file name and if the file exists read data settings 
	 *
     * @param fileName name of the file to load from
     * @throws std::runtime_error() if problems with I/O occur
     * 
     */
	void ProxySettings::load( string const &fileName )
	{
		std::ifstream file (fileName.c_str(), std::ifstream::in );

		if ( file.fail() )
    			throw std::runtime_error("Can't open \"" + fileName + "\" for reading");
		try
		{
			file >> data;	
		}
		catch ( std::runtime_error &e )
		{
			throw std::runtime_error ( "file \"" + fileName + "\" is not in ini format" );
		}
        
	}

}
