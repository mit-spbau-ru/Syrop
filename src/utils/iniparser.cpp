#include "iniparser.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <sstream>
#include <vector>

namespace utils {

using namespace boost::xpressive;
const sregex eSection = sregex::compile("^[\\ ]*\\[.*\\][\\ ]*$");
/**
 * 
 * checks if a string is represented in a section name format
 * true if the string contains unempty operator []
 *
 * @param str name of a string to check
 *
 */
bool isSection( string const &str ) 
{
    using namespace boost::xpressive;
    return regex_match( str, eSection );
}

/**
 * cuts off the part of string within comments
 * returns a string without commented part
 *
 * @param str a string to clean
 *
 */

string clean( string const &str )
{
    string newstr(str);
    size_t res = newstr.find('#');
    if (res == string::npos) return newstr;
    newstr.erase(newstr.begin() + res, newstr.end());
    return newstr; 

}

/**
 *
 * cuts the part of a string within [ ] brackets
 * check if the string is a section name first
 *
 * @param str a string to cut from
 * @throws std::runtime_error if string is not in the proper format
 *
 */
string extract( string const &str ) 
{
    if ( regex_match( str, eSection ) ) 
        return str.substr( 1, str.size() - 2 );
    else
        throw std::runtime_error( "string "+str+" is not section type\n" );
}

/**
 *
 * returns a pair of attribute - value of string
 * with regard to delimiter '='
 *
 * @param str a string to be splitted into the pair
 * @throws std::runtime_error if string is not in the proper format
 *
 */
pair <string, string> splice( string const &str ) 
{
    using namespace boost::xpressive;
    static const sregex e = sregex::compile("^[\\ ]*\\s(\\S+){1}\\s=\\s(\\S+){1}\\s[\\ ]*$");
    if ( regex_match( str, e ) ) {

        std::vector <string> splitVec;    
        boost::split( splitVec, str, boost::is_any_of("=") );	
        string first = splitVec[0];
        string second = splitVec[1];
        return std::make_pair(first, second);

    }
    else
        throw std::runtime_error( "string "+str+" is not of appropriate type \
                    attribute-setting\n" ); 
}

/**
 *
 * reads data from input stream
 *
 * @param is input string to read from
 * @param IniData object 
 *
 */

std::istream & operator >> ( std::istream &is, IniData & data )
{	
    string instr;
    string curSec = "";
    	
    while ( is ){

        getline(is,instr);
        instr = clean(instr);
		
        if ( isSection(instr) ){
            curSec = extract(instr);
            data.addSection(curSec);
        }
        else if ( !instr.empty() ) {
            if (curSec == "") throw std::runtime_error("file is not in ini format") ;

            std::pair<string, string> p = splice(instr);
            data.addAttribute( curSec,p );
        }		
    }
    return is;
}

/**
 *
 * writes data into stream file
 *
 * @param os output stream  
 * @param idata an object to store
 *
 */
std::ostream & operator << ( std::ostream &os, IniData const & idata )
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
    return os;
}

} //namespace utils
