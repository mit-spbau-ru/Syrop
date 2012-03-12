#include "../includes/stringutils.h"

namespace utils
{

std::vector<std::string> split(std::string const &str, std::string const &delim)
{
	std::vector<std::string> words;
	std::string::const_iterator left = str.begin();
	while ( left != str.end() )
	{
		while ( (left != str.end()) && (delim.find(*left) != std::string::npos) )
			++left;
			
		std::string::const_iterator right = left;
		while ( (right != str.end()) && (delim.find(*right) == std::string::npos) )
			++right;

		if (left != right)
		{
			words.push_back(std::string(left, right));
			left = right;
		}
	}
	
	return words;
}

} // namespace utils