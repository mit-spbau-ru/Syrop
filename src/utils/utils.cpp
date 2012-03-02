#include "utils.h"
#include <sstream>

namespace utils{

ProxySettings Parameters::getProxySettings(string& key){
	return params[key];
}

void ProxySettings::push(const string& key, const string& val){
	settings.insert(pair<string,string>(key,val));
}

bool Parameters::threshold (string& str){
	size_t res = str.find('#');
	if (res == str.npos) return false;
	str.erase(str.begin() + res);
	return true;	
}

bool Parameters::isProxyName(const string &str) const {
	return (str[0] == '[')&&(str[str.size()-1] == ']');
}
std::ostream & operator<<(std::ostream &os, ProxySettings &P){
	std::map<string,string>::iterator it;
	for (it = P.settings.begin(); it != P.settings.end(); it++){
			os <<  " " << it -> first << " " << it -> second << std::endl;			
	}
}

std::ostream & operator<<(std::ostream &os, Parameters &P){
	std::map<string,ProxySettings>::iterator it;
	for (it = P.params.begin(); it != P.params.end(); it++){
			os << "Proxy: " <<  it -> first << std::endl;
			os << it -> second;
	}

}

std::istream & operator>>(std::istream &is, Parameters &P){
	
	string instr;
	is >> instr;
	while (!is.eof()){
		string proxyName;	
		ProxySettings proxySettings;	
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
			proxySettings.push(key,value);
			std::cout << value << std::endl;
			
		}		
		P.params.insert(std::make_pair<string,ProxySettings>(proxyName,proxySettings));
		
	}
	return is;
}

} // namespace Utilities
