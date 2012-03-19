#ifndef _INCLUDES_PROXYSETTINGS_
#define _INCLUDES_PROXYSETTINGS_

#include "inidata.h"
#include "appsettings.h"
#include "iniparser.h"

namespace utils{

	class ProxySettings{
	
	public:

		AppSettings getAppSettings( string const &sec ) const;
		void loadData( string const &fileName );
		
		//void print() const;
		friend std::ostream& operator<<( std::ostream &os, ProxySettings const & ps );

	private:
		IniData data;
		
	};

}

#endif
