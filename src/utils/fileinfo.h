#ifndef _FILE_INFO_
#define _FILE_INFO_

#include <string>
#include <cerrno>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../includes/stringutils.h"

namespace utils {

	/**
	 * System information about file
	 */
	class FileInfo
	{
		public:
			FileInfo(std::string const &name)
			: myValidityFlag(false),
			myName(name)
			{}
			
			FileInfo()
			: myValidityFlag(false)
			{}
			
			/**
			 * Every FileInfo should be readed before using
			 *
			 * @throws SystemException if file isn't valid
			 */
			void read() throw(SystemException);
		
			/**
			 * Method return only name of file or directory. Example: for file '/home/mirovingen/aptu', aptu will be returned
			 *
			 * @return file name withot path
			 * @throws SystemException if file isn't valid
			 */
			std::string getName() const throw(SystemException)
			{
				validate();
				
				return utils::split(myName, std::string("/")).back();
			}
			
			/**
			 * Method returns full file name
			 *
			 * @return full file name
			 * @throws SystemException if file isn't valid
			 */
			std::string getFullName() const throw(SystemException)
			{
				validate();
				
				return myName;
			}
		
			/**
			 * If file is a directory returns true, otherwise false
			 *
			 * @return true if file is a directory
			 * @throws SystemException if file isn't valid
			 */
			bool isDirectory() const throw(SystemException)
			{
				validate();
			
				return S_ISDIR(myStat.st_mode);
			}
		
			/**
			 * If file is a regular file returns true, otherwise false
			 *
			 * @return true if file is a regular file
			 * @throws SystemException if file isn't valid
			 */
			bool isFile() const throw(SystemException)
			{
				validate();
			
				return S_ISREG(myStat.st_mode);
			}
		
			bool isValid() const
			{
				return myValidityFlag;
			}
		
		private:
			bool myValidityFlag;
			std::string myName;
			struct stat myStat;
		
			void validate() const throw(SystemException)
			{
				if (!isValid())
					throw SystemException("FileInfo isn't valid");
			}
	};
	
} // namespace utils

#endif //_FILE_INFO_