#ifndef _INCLUDES_GENUTILS
#define _INCLUDES_GENUTILS

#include <string>
#include <map>

namespace utils{

bool fileExists(std::string const &fname);

template < class T >
void makeConfig(std::string const &fname);

} //namespace utils

#endif
