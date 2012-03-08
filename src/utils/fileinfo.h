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
		
			void read() throw(SystemException)
			{
				const size_t msglen = 256;
				char msg[msglen];
				
				//get full path name
				char *fullPath = realpath(myName.c_str(), NULL);
				if (errno != 0)
					//throw SystemException if an error occurred
					throw SystemException(std::string(strerror_r(errno, msg, msglen)));
				myName.assign(fullPath);
				free(fullPath);

				//get file stat
				stat(myName.c_str(), &myStat);
				if (errno != 0)
					//throw SystemException if an error occurred
					throw SystemException(std::string(strerror_r(errno, msg, msglen)));
				
				//O.K.
				myValidityFlag = true;
			}
		
			std::string getName() const
			{
				validate();
				
				return utils::split(myName, std::string("/")).back();
			}
			
			std::string getFullName() const
			{
				validate();
				
				return myName;
			}
		
			bool isDirectory() const throw(SystemException)
			{
				validate();
			
				return S_ISDIR(myStat.st_mode);
			}
		
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