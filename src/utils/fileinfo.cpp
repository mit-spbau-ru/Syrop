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

void FileInfo::read() throw(SystemException)
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
	
} // namespace utils

#endif //_FILE_INFO_