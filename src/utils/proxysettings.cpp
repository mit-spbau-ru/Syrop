#include <iostream>
#include <fstream>

#include "proxysettings.h"

namespace utils{

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
