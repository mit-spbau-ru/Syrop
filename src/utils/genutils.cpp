#include <fstream>
#include <string>
#include "genutils.h"

namespace utils{
		
	bool fileExists(std::string const &fname)
	{
	  return std::ifstream( fname.c_str() ,  std::ifstream::in ) != NULL;
	}

	
	void makeConfig(std::string const &fname)
	{
		if (! fileExists(fname) )
		{	
			std::ofstream file;
			file.open ( fname.c_str() );
			file.close ();
		}

	}

} // namespace utils
