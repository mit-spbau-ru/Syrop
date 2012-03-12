#include "../includes/proxysettings.h"


namespace utils{

void AppProxySettings::push(string const &key, string const &val){
	settings.insert(pair<string,string>(key,val));
}

bool AppProxySettings::empty(){
	return settings.empty();
}

bool AppProxySettings::has(string const &str){
	return settings.find(str) != settings.end();
}


} // namespace utils
