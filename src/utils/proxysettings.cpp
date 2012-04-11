#include <fstream>
#include <stdexcept>
#include "proxysettings.h"

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

	ProxySettings :: const_iterator  ProxySettings::begin () const
	{
		 return data.begin();
	}

	ProxySettings :: const_iterator  ProxySettings::end () const
	{
		 return data.end();
	}

	ProxySettings :: iterator  ProxySettings::begin ()
    {
		return data.begin();
    }

    ProxySettings ::iterator  ProxySettings::end ()
    {
        return data.end();
    }

	void ProxySettings::saveData( IniData const &idata, string const &fileName  ) const
	{
		std::ofstream file(fileName.c_str());
		if (!file)
			throw std::runtime_error("Can't open \"" + fileName + "\" for writing");	
		writeData(file, idata);	
	}

	void ProxySettings::loadData( string const &fileName )
	{
		std::ifstream file (fileName.c_str(), std::ifstream::in );

		if ( file.fail() )
    		throw std::runtime_error("Can't open \"" + fileName + "\" for reading");	

		data = readData(file);	
        
	}

	std::ostream& operator<<( std::ostream &os, ProxySettings const & ps ) 
	{
		os << ps.data;
		return os;
	}

}
