#include "../includes/netparams.h"

namespace utils {

AppProxySettings NetworkProxyParameters::getAppProxySettings(string const &key)const{
	std::map<string, AppProxySettings>::const_iterator it = params.find(key);
	if (it == params.end()) return AppProxySettings();
	
	return it->second;
}

bool NetworkProxyParameters::threshold (string &str){
	size_t res = str.find('#');
	if (res == str.npos) return false;
	str.erase(str.begin() + res);
	return true;	
}

bool NetworkProxyParameters::isProxyName(string const &str) const {
	return (str[0] == '[')&&(str[str.size()-1] == ']');
}

} // namespace utils
