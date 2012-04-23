#include "iniparser.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <vector>

namespace utils {

// true if the string contains unempty operator []
bool isSectionName( string const &str ) 
{
	size_t from = str.find('[');
	size_t to = str.find(']');
	
	return (from != string::npos && to != string::npos && from < to);
}

// cuts off the part of string within comments
string cleanComments( string const &str )
{
	string newstr(str);
	size_t res = newstr.find('#');
	if (res == string::npos) return newstr;
	newstr.erase(newstr.begin() + res, newstr.end());
	return newstr;	

}

// cuts the part of a string within [ ] brackets
// check if the string is a section name first
string extractName( string const &str ) 
{
	size_t from = str.find('[');
	size_t to = str.find(']');

	return str.substr( from + 1, to - 1 );
}

// returns a pair of attribute - value of string
// with regard to delimiter '='
pair <string, string> getPair( string const &str ) 
{
	std::vector <string> splitVec;
	boost::split( splitVec, str, boost::is_any_of("=") );	
	string first = splitVec[0];
	string second = splitVec[1];
	return std::make_pair(first, second);
}

// reads data from input stream
void readData( std::istream &is, IniData & data )
{	
    string instr;
	string curSec;
    	
	while ( !is.eof() ){

		getline(is,instr);
		instr = cleanComments(instr);
		
		if ( isSectionName(instr) ){
			curSec = extractName(instr);
			data.addSection(curSec);
		}
		else if ( !instr.empty() ) {
			std::pair<string, string> p = getPair(instr);
			data.addAttribute( curSec,p );
		}		
	}
}

// writes data into stream file
void writeData( std::ostream &os, IniData const &idata )
{
	vector< string > secs = idata.getSectionsList();
	
	for ( vector< string >::const_iterator sit = secs.begin() ; sit != secs.end(); ++sit)
	{
		os << "[" << *sit << "]" << std::endl;
		attributes attrs = idata.getSection(*sit);

		for ( attributes::const_iterator ait = attrs.begin(); ait != attrs.end(); ++ait)
		{
			os << ait->first << "=" << ait->second << std::endl;
		}
	}

}

} //namespace utils
