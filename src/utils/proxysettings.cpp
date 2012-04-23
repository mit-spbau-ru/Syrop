#include <fstream>
#include <stdexcept>
#include "proxysettings.h"
#include "genutils.h"

namespace utils{


	bool ProxySettings::existsApp( string const &appName )
	{
		return data.hasSection ( appName ) ;
	}		

	// first call existsApp() is suggested to check if such an item exists in the map
	attributes & ProxySettings::operator[] (string const &appName)
	{
		return data [ appName ];	
	}

	
	// first call existsApp() is suggested to check if such an item exists in the map
	attributes const & ProxySettings::operator[] (string const &appName) const
	{
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
        if ( !fileExists( fileName ) ) 
            throw std::runtime_error( fileName + "\" does not exist ");
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

		readData( file, data );	
        
	}

	std::ostream& operator<<( std::ostream &os, ProxySettings const & ps ) 
	{
		os << ps.data;
		return os;
	}

}
