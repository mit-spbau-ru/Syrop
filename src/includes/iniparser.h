#ifndef _INCLUDES_INIPARSER_
#define _INCLUDES_INIPARSER_

#include <iostream>
#include <map>
#include <string>

#include "inidata.h"

namespace utils {

	IniData readData( std::istream &is );
	void writeData(std::ostream &os, IniData const &idata);

} // namespace utils

#endif
