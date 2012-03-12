#ifndef _PROXYSETTINGS
#define _PROXYSETTINGS

#include <iostream>
#include <map>
#include <string>

using std::string;
using std::pair;


namespace utils{
	
	//stores settings of a certain proxy profile 
	class AppProxySettings{
	
		std::map<string,string> settings;

		public:
			string& getProxy(string const&); 
			void push(string const&, string const&);
	
			bool empty();
			bool has(string const &);
			friend class IniParser;
			
	};

} // namespace utils
#endif
