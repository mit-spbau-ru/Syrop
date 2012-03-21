#include "appsettings.h"
#include "emptyobject.h"

namespace utils{
	
	attributes const & AppSettings::getAllAttributes() const 
	{
		return settings;
	}

	string AppSettings::getAttribute(string const &attrName) const
	{
		try 
		{
			if ( settings.find( attrName ) == settings.end() ) 
				throw EmptyObjectException();

		     return ( settings.find(attrName) )->second;
		}
		catch ( EmptyObjectException E )
		{
			std::cout << "AppSettings::getAttribute() : " << E.showReason() << std::endl;
		}
		return string();
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
