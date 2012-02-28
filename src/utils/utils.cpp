#include "utils.h"
#include <sstream>

namespace utilities{

ProxySettings Parameters::getProxySettings(string& key){
	return params[key];
}

void ProxySettings::push(string& key, string& val){
	settings.insert(pair<string,string>(key,val));
}

bool Parameters::threshold (string& str){
	size_t res = str.find('#');
	if (res == str.npos) return false;
	str.erase(str.begin() + res);
	return true;	
}

bool Parameters::isProxyName(string &str) const {
	return (str[0] == '[')&&(str[str.size()-1] == ']');
}

std::istream & operator>>(std::istream &is, Parameters &P){
	
	string instr;
	is >> instr;
	while (!is.eof()){
		string proxyName;	
		ProxySettings proxySettings;	
		size_t len_buf = 256;
		char buf[len_buf];

		if (P.threshold(instr))  {is.getline(buf,len_buf); is >> instr; continue;}
		if (!instr.empty() && P.isProxyName(instr)) proxyName  = instr.substr(1,instr.size()-2);
		
		while (!is.eof()){
			string key, value, eq;			
			is >> key;
			if (key.empty()) continue;
			
			if (P.threshold(key)) {is.getline(buf,len_buf); continue;}
			if (P.isProxyName(key)){instr = key; break;}
			is >> eq; 
			if (eq.empty()) continue;
			if (P.threshold(eq)) { is.getline(buf,len_buf); continue;} 
			is >> value;
			if (value.empty()) continue;
			if (P.threshold(value)) { is.getline(buf,len_buf); continue;}
			proxySettings.push(key,value);
			
		}		
		P.params.insert(pair<string,ProxySettings>(proxyName,proxySettings));
		
	}
	return is;
}

} // namespace Utilities
