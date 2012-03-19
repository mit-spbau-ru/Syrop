#ifndef _INCLUDES_SYSTEM_H_
#define _INCLUDES_SYSTEM_H_

#include <vector>
#include <string>

#include "fileinfo.h"

namespace utils {

	std::vector<FileInfo> listDirEntries(std::string const &dir);
	std::string getErrorMessage(int errCode);
	std::string getUserHomeDir();
	void createDir(std::string const &name);
	void createFile(std::string const &name);
	void removeFile(std::string const &name);

} // namespace utils

#endif //_INCLUDES_SYSTEM_H_