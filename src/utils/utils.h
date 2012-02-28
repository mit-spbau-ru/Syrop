#ifndef _UTILITIES
#define _UTILITIES

#include <iostream>
#include <map>
#include <string>

using std::string;
using std::pair;

namespace utilities{

	class ProxySettings{
	//stores settings of a certain proxy profile

		std::map<string,string> settings;

		public:
			string& getProxy(string&) const; // operator [] ?
			void push(string&, string&);
			void print(){
				std::map<string,string>::iterator it;
				for (it=settings.begin(); it != settings.end(); it++){
					std::cout <<  " " << it->first << " " << it->second << std::endl;			
				}
			}
			
	};

	class Parameters{
	//stores the structure of config.ini

		std::map<string,ProxySettings> params;
	
		bool threshold (string&);
		bool isProxyName(string &) const;
		public:

			friend std::istream & operator>>(std::istream &, Parameters &);		
			ProxySettings getProxySettings(string&);
			void print(){
				std::map<string,ProxySettings>::iterator it;
				for (it=params.begin(); it != params.end(); it++){
					std::cout << "Proxy: " <<  it->first << std::endl;
					it->second.print();
						
				}				
			}


	};

} // namespace Utilities
#endif
