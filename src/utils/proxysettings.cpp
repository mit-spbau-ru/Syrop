#include <iostream>
#include <fstream>
#include "emptyobject.h"
#include "proxysettings.h"

namespace utils{

	vector <AppSettings> ProxySettings::getAllSettings () const 
	{
		vector< AppSettings > as;
		vector< string > sl = data.getSectionsList();
		vector< string >::const_iterator slit = sl.begin(); 

		for ( ; slit != sl.end() ; ++slit) {

			string appName = *slit;
			as.push_back( AppSettings( appName, data.getSection(appName) ));
		}

		return as;
	}


	void ProxySettings::_save( AppSettings const & apps ) 
	{
		string name = apps.getApplicationName();
		data.removeSection( name );

		attributes settings = apps.getAllAttributes();
		attributes::const_iterator sit = settings.begin();

		data.addSection( name );
		for ( ; sit != settings.end() ; ++sit )
		{
			data.addAttribute(name, *sit);
		} 
		
	}

	
	void ProxySettings::save( AppSettings const & apps )
	{
		data.dropAll();
		_save ( apps );
		fix( data );		
	}



	void ProxySettings::save( vector < AppSettings > const & apps ) 
	{
		data.dropAll();
		vector <AppSettings> :: const_iterator asit = apps.begin();
		for ( ; asit != apps.end() ; ++asit )
		{
			_save (*asit);
		} 
		fix(data);
	}


	AppSettings ProxySettings::addNewApp( string const &name ) 
	{
		if ( data.hasSection( name ) ) return AppSettings();
		
		attributes attrs; // = data.getSection("default");
		AppSettings apps( name, attrs );
		save ( apps ) ;			
		return apps;

 	}

	AppSettings ProxySettings::getAppSettings( string const &appName ) const
	{
		try {	
			AppSettings aps = AppSettings( appName, data.getSection(appName) );
			return aps;
		}
		catch ( EmptyObjectException E ) 
		{

		}		
		return AppSettings();
	}

	void ProxySettings::loadData( string const &fileName )
	{
		this->fileName = fileName;
		IniParser iparser;
		std::ifstream file(fileName.c_str());
		if (file.is_open()){
			data = iparser.readData(file);	
		}	
		file.close();	
	}

	void ProxySettings::fix( IniData const &idata ) const
	{
		IniParser iparser;
		std::ofstream file(fileName.c_str());
		if (file.is_open()){
			iparser.writeData(file, idata);	
		}		
		file.close();
	}

	/*void ProxySettings::print() const {
		data.print();
	}*/

	std::ostream& operator<<( std::ostream &os, ProxySettings const & ps ) 
	{
		os << ps.data;
		return os;
	}

}
