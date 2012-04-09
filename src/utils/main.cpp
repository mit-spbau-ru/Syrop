#include <iostream>
#include "proxysettings.h"
#include "inidata.h"
#include <vector>
#include "genutils.h"
#include "emptyobject.h"
#include "system.h"

int main()
{
	using namespace utils;

	ProxySettings proxy;
	proxy.loadData("net_2.ini");
	std::cout << "data:" << std::endl;
	//std::cout << proxy;
	attributes attr = proxy["app2"];
	attributes::const_iterator pit = attr.begin();
	for ( ; pit != attr.end(); ++pit )
	{
		std::cout << pit->first << " " << pit->second << std::endl;
		
	}
		
//	vector < AppSettings > asets = proxy.getAllSettings();
	//std::cout << "asets before erase:" << asets.size() << std::endl;
	//asets.erase( asets.begin() + 1 );
	//std::cout << "asets after erase:" << asets.size() << std::endl;
	//proxy.save( asets );
	//std::cout << "data after erase:" << std::endl;
	//std::cout << proxy;
//	try {
//		AppSettings as = asets[0];
//		as["ssl_port"] = "3120";
//		std::cout << "got it" << std::endl;
//		std::cout << as["ssl_port"] << std::endl;
//	}
//	catch (EmptyObjectException& t)
//	{
//		std::cout << "too short: " << asets.size() << std::endl;
//	}
	//asets[0]['ssl_port'] = 3130;
	//utils::create_dir("~/folder/aaaa");	

	return 0;
}
