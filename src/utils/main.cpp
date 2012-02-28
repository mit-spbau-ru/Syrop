#include <iostream>
#include "utils.h"

#define _DEBUG
using namespace utilities;
int main(){
	
	Parameters p;
	std::cin >> p;
	#ifdef _DEBUG
	p.print();
	#endif
	return 0;
}
