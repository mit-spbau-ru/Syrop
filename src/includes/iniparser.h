#ifndef _INIPARSER
#define _INIPARSER

#include <iostream>
#include <map>
#include <string>

#include "proxysettings.h"
#include "netparams.h"

using std::string;
using std::pair;


namespace utils {

	struct IniParser {
		void showAppProxySettings(std::ostream&, AppProxySettings const&);
		void readNetworkProxySettings(std::istream&, NetworkProxyParameters&);	
		void showNetworkProxySettings(std::ostream&, NetworkProxyParameters const&);	
	};
			

} // namespace utils

#endif
