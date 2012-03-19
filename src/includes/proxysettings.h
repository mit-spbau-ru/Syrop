#ifndef _INCLUDES_PROXYSETTINGS_
#define _INCLUDES_PROXYSETTINGS_

#include "inidata.h"
#include "appsettings.h"
#include "iniparser.h"

namespace utils{

	class ProxySettings
	{
	
	public:

		void loadData( string const &fileName );
		void fix( IniData const &idata );

		AppSettings getAppSettings( string const &sec ) const;
		vector< AppSettings > getAllSettings () const;

		void save ( AppSettings const & apps ) ;
		AppSettings addNewApp( string const &name ) ;

		//void print() const;
		friend std::ostream& operator<<( std::ostream &os, ProxySettings const & ps );

	private:
		IniData data;
		string fileName;
		
	};

}

#endif
