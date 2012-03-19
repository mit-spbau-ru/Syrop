#include "iniparser.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <vector>

namespace utils {

bool IniParser::isSectionName( string const &str ) 
{
	size_t from = str.find('[');
	size_t to = str.find(']');
	
	return (from != string::npos && to != string::npos);
}

string IniParser::cleanComments( string const &str )
{
	string newstr(str);
	size_t res = newstr.find('#');
	if (res == string::npos) return newstr;
	newstr.erase(newstr.begin() + res, newstr.end());
	return newstr;	

}

string IniParser::adjust( string const &str ) 
{
	size_t from = str.find('[');
	size_t to = str.find(']');

	return str.substr( from + 1, to - 1 );
}

pair <string, string> IniParser::getPair( string const &str ) 
{
	std::vector <string> splitVec;
	boost::split( splitVec, str, boost::is_any_of("=") );	
	string first = splitVec[0];
	string second = splitVec[1];
	return std::make_pair(first, second);
}


IniData IniParser::readData(std::istream &is) const
{
	IniData data;
	string instr;

	string curSec;	
	while ( !is.eof() ){

		getline(is,instr);
		instr = cleanComments(instr);
		
		if ( isSectionName(instr) ){
			curSec = adjust(instr);
			data.addSection(curSec);
		}
		else if ( !instr.empty() ) {
			std::pair<string, string> p = getPair(instr);
			data.addAttribute( curSec,p );
		}		
	}
	return data;

}


/*void IniParser::showAppProxySettings(std::ostream &os, AppProxySettings const &P)
{
	std::map<string, string>::const_iterator it;
	for (it = P.settings.begin(); it != P.settings.end(); it++){
			os <<  " " << it -> first << " " << it -> second << std::endl;			
	}
}*/

/*void IniParser::showNetworkProxySettings(std::ostream &os, NetworkProxyParameters const &P)
{
	std::map<string, AppProxySettings>::const_iterator it;
	for (it = P.params.begin(); it != P.params.end(); it++){
			os << "Proxy: " <<  it -> first << std::endl;
			showAppProxySettings(os,it -> second);
	}

}*/

} //namespace utils
