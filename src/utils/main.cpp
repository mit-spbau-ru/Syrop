#include <iostream>
#include "utils.h"

using namespace utils;
int main(){
	
	Parameters p;
	std::cin >> p;
	#ifdef _DEBUG
	p.print();
	#endif
	return 0;
}
