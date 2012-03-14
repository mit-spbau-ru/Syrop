#ifndef _INCLUDES_INIPARSER_
#define _INCLUDES_INIPARSER_

#include <iostream>
#include <map>
#include <string>

#include "inidata.h"

namespace utils {

	class IniParser {

	public:

		IniData readData( std::istream &is ) const;

	private:
		static bool isSectionName( string const &str ) ;
		static string cleanComments( string const &str );
		static string adjust( string const &str ) ;
		static pair <string, string> getPair( string const &str );

		//void showAppProxySettings( std::ostream&, AppProxySettings const& );	
		//void showNetworkProxySettings( std::ostream&, NetworkProxyParameters const& );
	
	};
			

} // namespace utils

#endif
