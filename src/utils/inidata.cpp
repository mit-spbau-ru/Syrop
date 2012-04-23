#include <iostream>
#include <string>
#include <map>
#include "inidata.h"

using std::string;
using std::map;

namespace utils{

    // add a new section within [] brackets
    // if such a section already exists nothing happens
    // check it with the hasSection() method first
	void IniData::addSection( string const & sec )
	{
		data.insert( make_pair(sec, attributes()) );
	}

    // add a pair attribute-value within a section sec
    // if such an attribute already exists nothing happens
    // check it with the hasAtttribute() method first
	void IniData::addAttribute( string const &sec, pair <string, string> const &params )
	{
		data[sec].insert(params);
	}

	bool IniData::hasSection( string const &sec ) const
	{
		return data.find(sec) != data.end();		
	}

    // first call hasSection() is suggested to check if such an item exists in the map
    attributes & IniData::operator[] ( string const &appName )
    {
        return data [ appName ];        

    }

        
    // first call hasSection() is suggested to check if such an item exists in the map
    attributes const & IniData::operator[] ( string const &appName ) const
    {
       return data.find( appName ) -> second;
    }

	
	bool IniData::hasAttribute( string const &sec, string const &attr ) const
	{
		if ( hasSection( sec ) )
		{
			attributes attrs = getSection( sec );
			attributes::const_iterator  ait = attrs.find( attr );
			return ( ait != attrs.end() ) ;
		}		
		return false;
	}

	void IniData::removeSection( string const &sec ) 
	{
		attributes_map::iterator dit = data.find( sec );
		if ( dit != data.end() ) data.erase ( dit );		
		return;
	}

	attributes IniData::getSection( string const &sec ) const
	{
		attributes_map::const_iterator it = data.find( sec );
		if ( it == data.end() )
    			return attributes();
		else
			return it->second;
		
	}

    IniData::const_iterator  IniData::begin () const
    {
        return data.begin();
    }
    IniData::const_iterator  IniData::end () const
    {
        return data.end();
    }

    IniData::iterator  IniData::begin ()
    {
        return data.begin();
    }
    IniData::iterator IniData::end ()
    {
        return data.end();
    }



//	attributes & IniData::operator [] ( string const & secName ) 
//	{
//		return data [ secName ]; 
//	}

//	attributes const & IniData::operator [] ( string const & secName) const
//	{
//		return data.find ( secName ) -> second ;
//	}

    // creates a list of all sections in the current data
	vector< string > IniData::getSectionsList() const
	{
		vector<string> secs;
		
		for ( attributes_map::const_iterator it = data.begin();  it != data.end() ; ++it ) {
			secs.push_back( it->first );
		}
		return secs;
	}
		std::ostream& operator<<( std::ostream &os, IniData const &idata ) 
	{
	    for ( attributes_map::const_iterator ait = idata.data.begin(); ait != idata.data.end(); ++ait){
			os <<  " " << ait -> first << std::endl; 
			for (attributes::const_iterator sit = ait->second.begin() ; sit != ait->second.end() ; ++sit ) 
			 	os << "   " << sit -> first  << " " << sit -> second << std::endl;			
		}
		return os;
	}
	
}
