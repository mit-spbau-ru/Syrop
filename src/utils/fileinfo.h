#ifndef _FILE_INFO_
#define _FILE_INFO_

#include <string>
#include <cerrno>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
			
				stat(myName.c_str(), &myStat);
				if (errno != 0)
				{
					throw SystemException(std::string(strerror_r(errno, msg, msglen)));
				}
				myValidityFlag = true;
			}
		
			std::string getName() const
			{
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