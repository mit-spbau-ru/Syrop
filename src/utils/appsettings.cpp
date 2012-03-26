#include "appsettings.h"
#include "emptyobject.h"

namespace utils{
	
	attributes const & AppSettings::getAllAttributes() const 
	{
		return settings;
	}



	string const &  AppSettings::operator[](string const &attrName) const
	{		
		if ( settings.find( attrName ) == settings.end() ) 
				throw EmptyObjectException();

		     return ( settings.find(attrName) )->second;	
	}

	string &  AppSettings::operator[](string const &attrName)
	{
		if ( settings.find( attrName ) == settings.end() ) 
				throw EmptyObjectException();

		     return ( settings.find(attrName) )->second;
		
	}


}
