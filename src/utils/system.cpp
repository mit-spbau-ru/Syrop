#include <dirent.h>
#include <sys/types.h>

#include <string>
#include <vector>
#include <cerrno>
#include <cstring>
#include <cstdlib>

#include "fileinfo.h"
#include "sysexception.h"

namespace utils {

/**
 * Returns error message returned by strerror_r
 *
 * @param errCode error code
 */
std::string getErrorMessage(int errCode)
{
	static const size_t maxLen = 256;
	static char msgBuf[maxLen] = {};
	return std::string(strerror_r(errCode, msgBuf, maxLen));
}

/**
 * Function list all directory entries in a directory specified by argument
 *
 * @param dir directory name
 * @return vector of FileInfo
 * @throws std::exception if an I/O error occured
 */
std::vector<FileInfo> listDirEntries(std::string const &dir) // throws SystemException
{
	DIR *dp = 0;
	dirent *result = 0;
	dirent entry;
	std::vector<FileInfo> names;
	
	if ( ( dp = opendir(dir.c_str()) ) == NULL)
		//if an error occured throw SystemException
		throw SystemException(getErrorMessage(errno));
	
	int r = 0;
	while ( ( (r = readdir_r(dp, &entry, &result) ) == 0 ) && ( result != NULL ) )
		names.push_back(FileInfo(dir + "/" + entry.d_name));
	
	closedir(dp);
	
	//test an error	
	if (errno != 0)
		//throw SystemException if an error occured
		throw SystemException(getErrorMessage(errno));
	
	return names;
}

/**
 * Returns user home dir defined in environment variable HOME
 *
 * @throws std::exception if there isn't variable HOME
 */
std::string getUserHomeDir() // throws sSystemException
{
	char *home = getenv("HOME");
	if (home == NULL)
		throw SystemException("Environment variable HOME not found");
	return std::string(home);
}

} // namespace utils
