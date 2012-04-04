#include <iostream>
#include <fstream>
#include "emptyobject.h"
#include "proxysettings.h"

namespace utils{

	attributes_map ProxySettings::getAllSettings () const 
	{
		return settings;
	}


	void ProxySettings::saveIniData( attributes const & apps, string const & name ) 
	{
		data.removeSection( name );

		attributes::const_iterator ait = apps.begin();

		data.addSection( name );
		for ( ; ait != apps.end() ; ++ait )
		{
			data.addAttribute(name, *ait);
		} 
		
	}

	bool ProxySettings::existsApp( string const &appName )
	{
		return settings.find( appName ) != settings.end() ;


	}		

	// first call existsApp() is suggested to check if such a name exists in map
	attributes& ProxySettings::operator[] (string const &appName)
	{
		return settings[ appName ];	

	}

	
	// first call existsApp() is suggested to check if such a name exists in map
	attributes const& ProxySettings::operator[] (string const &appName) const
	{
		return settings.find( appName ) -> second;
	}

	


	void ProxySettings::save( ) 
	{
		data.dropAll();
		attributes_map :: const_iterator sit = settings.begin();
		for ( ; sit != settings.end() ; ++sit )
		{
			saveIniData ( sit->second, sit->first );
		} 
		fix(data);
	}


	// checks if the application of name name exists
	// in this case returns its settings
	// else adds a new application  
	// and returns a reference to the empty settings
	attributes& ProxySettings::addApp( string const &name ) 
	{
				
		attributes_map :: const_iterator res = settings.find( name );	
		if ( res != settings.end() ) return settings[name] ;

		attributes attrs;
		settings.insert ( make_pair ( name, attrs ) ); 
		save () ;			
		return settings[ name ];

 	}

	void ProxySettings::removeApp( string const & name )
	{
		if ( existsApp (name) ) 
		{
			settings.erase ( settings.find (name) );
		}
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
