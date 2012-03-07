#include "../includes/iniparser.h"
#include <sstream>

namespace utils {

void IniParser::showAppProxySettings(std::ostream &os, AppProxySettings const &P){
	std::map<string, string>::const_iterator it;
	for (it = P.settings.begin(); it != P.settings.end(); it++){
			os <<  " " << it -> first << " " << it -> second << std::endl;			
	}
}

void IniParser::showNetworkProxySettings(std::ostream &os, NetworkProxyParameters const &P){
	std::map<string, AppProxySettings>::const_iterator it;
	for (it = P.params.begin(); it != P.params.end(); it++){
			os << "Proxy: " <<  it -> first << std::endl;
			showAppProxySettings(os,it -> second);
	}

}

void IniParser::readNetworkProxySettings(std::istream &is, NetworkProxyParameters &P){
	
	string instr;
	is >> instr;
	while (!is.eof()){
		string proxyName;	
		AppProxySettings apSettings;	
		string buf;

		if (P.threshold(instr))  {getline(is,buf);  is >> instr; continue;}
		if (!instr.empty() && P.isProxyName(instr)) proxyName  = instr.substr(1,instr.size() - 2);
		
		while (!is.eof()){
			string key, value, eq;			
			is >> key;
			if (key.empty()) continue;
			
			if (P.threshold(key)){
				getline(is,buf); 
				continue;
			}
			if (P.isProxyName(key)){
				instr = key; 
				break;
			}
			is >> eq; 
			if (eq.empty()) continue;
			if (P.threshold(eq)) {
				getline(is,buf); 
				continue;
			} 
			getline(is,value);
			if (value.empty()) continue;
			if (P.threshold(value)) {
				getline(is,buf); 
				continue;
			}
			apSettings.push(key,value);
			
		}		
		P.params.insert(std::make_pair<string,AppProxySettings>(proxyName,apSettings));
		
	}

}
} //namespace utils
