#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#include <vector>
#include <string>

namespace utils
{

	std::vector<std::string> split(std::string const &str, std::string const &delim);
	
} // namespace utils

#endif //_STRING_UTILS_H_