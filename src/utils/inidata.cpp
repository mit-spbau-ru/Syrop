#include <iostream>
#include <string>
#include <map>
#include "inidata.h"

using std::string;
using std::map;

namespace utils{

	/**
	 * add a new section within [] brackets
	 * if such a section already exists nothing happens
	 * check it with the hasSection() method first
     * 
     * @param sec name of the section to add
     *
	 */
	void IniData::addSection( string const & sec )
	{
		data.insert( make_pair( sec, attributes() ) );
	}

	/**
	 * add a pair attribute-value within a section sec
	 * if such an attribute already exists nothing happens
	 * check it with the hasAtttribute() method first
     *
     * @param sec name of the section where the attribute is added
     * @param a pair of attribute and its value
     *
	 */
	void IniData::addAttribute( string const &sec, pair <string, string> const &params )
	{
		data[sec].insert(params);
	}

	bool IniData::hasSection( string const &sec ) const
	{
		return data.find(sec) != data.end();		
	}

	/**
	 * returns a reference to the attributes of the given section 
     * first call hasSection() is suggested to check if such an item exists in the map
     *
     * @param appName a name of application to get settings
     *
	 */
	attributes & IniData::operator[] ( string const &appName ) { return data [appName]; }

        
	/**
	 * first call hasSection() is suggested to check if such an item exists in the map
	 * returns a constant reference to the attributes of the given section 
     *
     * @param appName a name of application to get settings
	 *
     */
	attributes const & IniData::operator[] ( string const &appName ) const
	{
		return data.find(appName)->second;
	}

    /**
     * 
     * checks if such an attributes exists within such a section
     *
     * @param sec a name of the section 
     * @param attr a name of the attribute to look up
     *
     */
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

    /**
     * 
     * removes a section from the class object
     *
     * @param sec a name of the section 
     *
     */   
    void IniData::removeSection( string const &sec ) 
	{
		attributes_map::iterator dit = data.find( sec );
		if ( dit != data.end() ) data.erase ( dit );		
		return;
	}

    /**
     * 
     * returns attributes of a specified section 
     * if such a section does not exist returns empty object
     *
     * @param sec a name of the section 
     *
     */
	attributes IniData::getSection( string const &sec ) const
	{
		attributes_map::const_iterator it = data.find( sec );
		if ( it == data.end() )
    			return attributes();
		else
			return it->second;
		
	}

    /**
     * constant iterator to the begining of data object 
     */
	IniData::const_iterator  IniData::begin() const { return data.begin(); }
    
    /**
     * constant iterator to the end of data object 
     */
	IniData::const_iterator  IniData::end() const { return data.end(); }

    /**
     * iterator to the begining of data object 
     */
	IniData::iterator  IniData::begin() { return data.begin(); }

    /**
     * iterator to the end of data object 
     */
	IniData::iterator IniData::end() { return data.end(); }

	/**
	 * creates a list of all sections in the current data
	 */
	vector< string > IniData::getSectionsList() const
	{
		vector<string> secs;
		
		for ( attributes_map::const_iterator it = data.begin();  it != data.end() ; ++it )
		{
			secs.push_back( it->first );
		}
		return secs;
	}
}
