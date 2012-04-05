#include <iostream>
#include <fstream>
#include "emptyobject.h"
#include "proxysettings.h"

namespace utils{


	bool ProxySettings::existsApp( string const &appName )
	{
		return data.hasSection ( appName ) ;

	}		
/*
	// first call existsApp() is suggested to check if such a name exists in map
	attributes& ProxySettings::operator[] (string const &appName)
	{
		return data [ appName ];	

	}

	
	// first call existsApp() is suggested to check if such a name exists in map
	attributes const& ProxySettings::operator[] (string const &appName) const
	{
		//return settings.find( appName ) -> second;
		return data [ appName ];
	}
*/
	

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

	void ProxySettings::save(  ) 
	{
		fix( data );
	}

		
	void ProxySettings::loadData( string const &fileName )
	{
		this->fileName = fileName;
		std::ifstream file(fileName.c_str());
		
		if (file.is_open()){
			data = readData(file);	
		}	
		file.close();

	
	}

	void ProxySettings::fix( IniData const &idata ) const
	{
		std::ofstream file(fileName.c_str());
		if (file.is_open()){
			writeData(file, idata);	
		}		
		file.close();
	}


	std::ostream& operator<<( std::ostream &os, ProxySettings const & ps ) 
	{
		os << ps.data;
		return os;
	}

}
