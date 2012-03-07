#ifndef _NETPARAMS
#define _NETPARAMS

#include <iostream>
#include <map>
#include <string>

#include "proxysettings.h"

using std::string;
using std::pair;


namespace utils{

	//stores the structure of config.ini
	class NetworkProxyParameters{	

		std::map<string, AppProxySettings> params;
	
		bool threshold (string&);
		bool isProxyName(string const&) const;
		public:

			//friend std::istream & operator>>(std::istream&, Parameters&);	
			//friend std::ostream & operator<<(std::ostream&, Parameters const&);	
			AppProxySettings getAppProxySettings(string const&) const;

			string getProxy(string const&) const;

			friend class IniParser;

	};


} //namespace utils



#endif
