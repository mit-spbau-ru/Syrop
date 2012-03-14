#ifndef _INCLUDES_FILEINFO_H_
#define _INCLUDES_FILEINFO_H_

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace utils {

	/**
	 * System information about file
	 */
	class FileInfo
	{
	public:
		FileInfo(std::string const &name) // throws std::runtime_error
		: myName(name)
		{
			read();
		}
		
		FileInfo()
		{}
	
		/**
		 * Method return only name of file or directory. Example: for file
		 * '/home/mirovingen/aptu', aptu will be returned
		 *
		 * @return file name withot path
		 */
		std::string getName() const
		{
			std::vector<std::string> splitVec;
			boost::split(splitVec, myName, boost::algorithm::is_any_of("/"));
			return splitVec.back();
		}
		
		/**
		 * Method returns full file name
		 *
		 * @return full file name
		 */
		std::string getFullName() const
		{
			return myName;
		}
	
		/**
		 * If file is a directory returns true, otherwise false
		 *
		 * @return true if file is a directory
		 */
		bool isDirectory() const
		{
			return S_ISDIR(myStat.st_mode);
		}
	
		/**
		 * If file is a regular file returns true, otherwise false
		 *
		 * @return true if file is a regular file
		 */
		bool isFile() const
		{
			return S_ISREG(myStat.st_mode);
		}
	
	private:
		std::string myName;
		struct stat myStat;
		
		void read(); // throws std::runtime_error
	};
	
} // namespace utils

#endif //_INCLUDES_FILEINFO_H_