#ifndef _UTILITIES
#define _UTILITIES

#include <iostream>
#include <map>
#include <string>

using std::string;
using std::pair;

namespace utils{
	
	//stores settings of a certain proxy profile
	class ProxySettings{
	
		std::map<string,string> settings;

		public:
			string& getProxy(const string&); 
			void push(const string&, const string&);
			friend std::ostream & operator<<(std::ostream &, const ProxySettings &);
			
	};

	//stores the structure of config.ini
	class Parameters{	

		std::map<string,ProxySettings> params;
	
		bool threshold (string&);
		bool isProxyName(const string &) const;
		public:

			friend std::istream & operator>>(std::istream &, Parameters &);	
			friend std::ostream & operator<<(std::ostream &, const Parameters &);	
			ProxySettings getProxySettings(const string&) const;

	};

} // namespace utils
#endif
