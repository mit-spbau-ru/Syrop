#include <iostream>
#include <string>
#include <map>
#include "inidata.h"

using std::string;
using std::map;

namespace utils{

	void IniData::addSection( string const & sec )
	{
		data.insert( make_pair(sec, attributes()) );
	}

	void IniData::addAttribute( string const &sec, pair <string, string> const &params )
	{
		data[sec].insert(params);
	}

	//void IniData::removeSection(string const &);
	//void IniData::removeAttribute(string const &);
	
	bool IniData::hasSection( string const &sec ) const
	{
		return data.find(sec) != data.end();		
	}
	
	attributes IniData::getSection( string const &sec ) const
	{
		return (data.find(sec))->second;
	}
	//string IniData::getAttribute(string const &){
	//}

/*	void IniData::print() const {

		std::map<string, attributes>::const_iterator ait = data.begin();

		for ( ; ait != data.end(); ++ait){
			std::cout <<  " " << ait -> first << std::endl; 
			for (attributes::const_iterator sit = ait->second.begin() ; sit != ait->second.end() ; ++sit ) 
			 	std::cout << "   " << sit -> first  << " " << sit -> second << std::endl;			
		}

	}
*/

	std::ostream& operator<<( std::ostream &os, IniData const &idata ) 
	{

		std::map<string, attributes>::const_iterator ait = idata.data.begin();

		for ( ; ait != idata.data.end(); ++ait){
			os <<  " " << ait -> first << std::endl; 
			for (attributes::const_iterator sit = ait->second.begin() ; sit != ait->second.end() ; ++sit ) 
			 	os << "   " << sit -> first  << " " << sit -> second << std::endl;			
		}
		return os;
				

	}
	
}
