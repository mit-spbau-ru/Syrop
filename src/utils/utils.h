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
			string& getProxy(const string&) const; // operator [] ?
			void push(const string&, const string&);
			void print(){
				std::map<string,string>::iterator it;
				for (it = settings.begin(); it != settings.end(); it++){
					std::cout <<  " " << it -> first << " " << it -> second << std::endl;			
				}
			}
			
	};

	//stores the structure of config.ini
	class Parameters{	

		std::map<string,ProxySettings> params;
	
		bool threshold (string&);
		bool isProxyName(const string &) const;
		public:

			friend std::istream & operator>>(std::istream &, Parameters &);		
			ProxySettings getProxySettings(string&);
			void print(){
				std::map<string,ProxySettings>::iterator it;
				for (it = params.begin(); it != params.end(); it++){
					std::cout << "Proxy: " <<  it -> first << std::endl;
					it -> second.print();
						
				}				
			}


	};

} // namespace utils
#endif
