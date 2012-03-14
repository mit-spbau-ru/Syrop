#include "appsettings.h"

namespace utils{
	
	string AppSettings::getAttribute(string const &attrName) const
	{
		return (settings.find(attrName))->second;
	}

	bool AppSettings::hasAttribute(string const &attrName) const
	{
		return (settings.find(attrName) != settings.end());
	}
}
