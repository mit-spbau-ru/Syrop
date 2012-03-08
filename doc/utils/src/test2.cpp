#include <iostream>
#include <vector>
#include <string>

#include "stringutils.h"

int main(int argc, char **argv)
{
	std::string str(argv[1]);
	std::string delim(argv[2]);
	std::vector<std::string> words = utils::split(str, delim);
	for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it)
		std::cout << *it << std::endl;
	
	return 0;
}