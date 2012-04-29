#include <fstream>
#include <stdexcept>
#include "proxysettings.h"
#include "genutils.h"

namespace utils{


	bool ProxySettings::existsApp( string const &appName ) const
	{
		return data.hasSection ( appName ) ;
	}		
    
    void ProxySettings::removeApp( string const &appName )
	{
		if ( !data.hasSection ( appName ) )
            throw std::runtime_error( "there is no \"" + appName + "\" application to erase" );
        data.removeSection( appName ) ;
	}		
 
	// first call existsApp() is suggested to check if such an item exists in the map
	attributes & ProxySettings::operator[] (string const &appName)
	{
        if ( ! existsApp(appName) )
            if ( existsApp( "default" ) )  return data[ "default" ];
            else return attributes() ;
		return data [ appName ];	
	}

	
	// first call existsApp() is suggested to check if such an item exists in the map
	attributes const & ProxySettings::operator[] (string const &appName) const
	{    
        if ( ! existsApp(appName) )
            if ( existsApp( "default" ) )  return data[ "default" ];
            else return attributes();
		return data [ appName ];
	}

    // returns a const iterator to the beginning of the data stored
	ProxySettings :: const_iterator  ProxySettings::begin () const
	{
		 return data.begin();
	}

    // returns a const iterator to the end of the data stored
	ProxySettings :: const_iterator  ProxySettings::end () const
	{
		 return data.end();
	}

    // returns an iterator to the beginning of the data stored
	ProxySettings :: iterator  ProxySettings::begin ()
    {
		return data.begin();
    }

    // returns an iterator to the end of the data stored
    ProxySettings ::iterator  ProxySettings::end ()
    {
        return data.end();
    }


    // get a file name and if the file exists write data settings
    // in it    
	void ProxySettings::save( string const &fileName  ) const
	{
		std::ofstream file(fileName.c_str());
		if (!file)
			throw std::runtime_error("Can't open \"" + fileName + "\" for writing");	
		writeData( file, data );	
	}

    // get a file name and if the file exists read data settings 
	void ProxySettings::loadData( string const &fileName )
	{
		std::ifstream file (fileName.c_str(), std::ifstream::in );

		if ( file.fail() )
    		throw std::runtime_error("Can't open \"" + fileName + "\" for reading");	
        try {
		    readData( file, data );	
        }
        catch ( std::runtime_error &e )
        {
            throw std::runtime_error ( "file \"" + fileName + "\" is not in ini format" );
        }
        
	}

}
