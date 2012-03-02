#include <iostream>
#include "utils.h"

using namespace utils;
int main(){
	
	Parameters p;
	std::cin >> p;
	
	#ifdef _DEBUG
	std::cout << p;
	#endif
	return 0;
}
