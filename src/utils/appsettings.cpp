#include "appsettings.h"

namespace utils{
	
	attributes const & AppSettings::getAllAttributes() const 
	{
		return settings;
	}

	string AppSettings::getAttribute(string const &attrName) const
	{
		return ( settings.find(attrName) )->second;
	}

	bool AppSettings::hasAttribute(string const &attrName) const
	{
		return ( settings.find(attrName) != settings.end() );
	}

	void AppSettings::setAttribute(string const &attrName, string const &attrVal)
	{
		attributes::iterator sit = settings.find(attrName);
		if ( sit == settings.end() )
		{
			settings.insert( make_pair (attrName, attrVal) );
		}
		else
		{
			settings.erase( sit );
			settings.insert( make_pair (attrName, attrVal) );
		}	
	}
}
