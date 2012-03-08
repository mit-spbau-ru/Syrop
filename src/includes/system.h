#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "../utils/sysexception.h"
#include "../utils/fileinfo.h"

namespace utils {

	std::vector<FileInfo> listDirEntries(std::string const &dir) throw(SystemException);
	FileInfo getFileInfo(std::string const &name) throw(SystemException);

} // namespace utils

#endif //_SYSTEM_H_