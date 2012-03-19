#ifndef _INCLUDES_APPSETTINGS_
#define _INCLUDES_APPSETTINGS_

#include "inidata.h"
#include <string>

namespace utils{
	
	class AppSettings{

	public:
		AppSettings( string const& app, attributes const &settings )
		: app(app)
		, settings(settings)
		{}
		AppSettings () {}
		
		string getAttribute(string const &attrName) const;
		void setAttribute(string const &attrName, string const &attrVal);
		attributes const & getAllAttributes() const;
		bool hasAttribute(string const &attrName) const;
		string getApplicationName() const {return app;}

	private:
		std::string app;
		attributes settings;	
	};

}

#endif
