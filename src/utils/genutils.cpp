#include <fstream>
#include <string>
#include "genutils.h"

namespace utils{
		
	bool fileExists(std::string const &fname)
	{
	  return std::ifstream( fname.c_str() ,  std::ifstream::in ) != NULL;
	}


	template < class T >	
	void makeConfig(std::string const &fname, T const & configer )
	{
		if (! fileExists(fname) )
		{	
			std::ofstream file;
			file.open ( fname.c_str() );
			
			configer.generate(file);

			file.close ();
		}

	}

} // namespace utils
