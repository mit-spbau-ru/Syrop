#include <iostream>
#include <fstream>

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
 
	AppSettings ProxySettings::getAppSettings( string const &appName ) const
	{
		return AppSettings( appName, data.getSection(appName) );
	}

	void ProxySettings::loadData( string const &fileName )
	{
		IniParser iparser;
		std::ifstream file(fileName.c_str());
		if (file.is_open()){
			data = iparser.readData(file);	
		}		
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
