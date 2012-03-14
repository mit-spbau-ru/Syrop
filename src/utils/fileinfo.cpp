#include <cstdlib>
#include <cerrno>
#include <exception>
#include <boost/shared_ptr.hpp>

#include "fileinfo.h"
#include "system.h"

namespace utils {

void FileInfo::read() // throws std::runtime_error
{	
	errno = 0;
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
		throw std::runtime_error(getErrorMessage(errCode) + " at FileInfo::read on " + myName);
}

} // namespace utils