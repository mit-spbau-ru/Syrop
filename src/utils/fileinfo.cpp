#include <cstdlib>
#include <cerrno>
#include <boost/shared_ptr.hpp>

#include "fileinfo.h"
#include "sysexception.h"
#include "system.h"

namespace utils {

void FileInfo::read() // throws SystemException
{	
	//get full path name
	boost::shared_ptr<char> fullPath(realpath(myName.c_str(), NULL), free);
	int errCode = errno;
	if (errCode == 0) {
		myName.assign(fullPath.get());
		//get file stat
		stat(myName.c_str(), &myStat);
		errCode = errno;
	}
	if (errCode != 0)
		//throw SystemException if an error occurred
		throw SystemException(getErrorMessage(errCode));
}

} // namespace utils