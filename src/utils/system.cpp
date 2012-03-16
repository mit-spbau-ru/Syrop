#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <string>
#include <vector>
#include <cerrno>
#include <cstring>
#include <exception>

#include "fileinfo.h"

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
 * @throws std::runtime_error if an I/O error occured
 */
std::vector<FileInfo> listDirEntries(std::string const &dir) // throws std::runtime_error
{
	DIR *dp = 0;
	dirent *result = 0;
	dirent entry;
	std::vector<FileInfo> names;
	
	errno = 0;
	
	if ( ( dp = opendir(dir.c_str()) ) == NULL)
		//if an error occured throw std::runtime_error
		throw std::runtime_error(getErrorMessage(errno) + " at listDirEntries on " + dir);
	
	while ( ( readdir_r(dp, &entry, &result) == 0 ) && ( result != NULL ) )
	{
		std::string name(entry.d_name);
		if (name != "." && name != "..")
			names.push_back(FileInfo(dir + "/" + entry.d_name));
	}
	
	//test an error	
	if (errno != 0)
		//throw std::runtime_error if an error occured
		throw std::runtime_error(getErrorMessage(errno) + " at listDirEntries on " + dir);
	
	closedir(dp);
	
	return names;
}

/**
 * Returns user home dir defined in environment variable HOME
 *
 * @throws std::runtime_error if there isn't variable HOME
 */
std::string getUserHomeDir() // throws std::runtime_error
{
	char const * const home = getenv("HOME");
	if (home == NULL)
		throw std::runtime_error("Environment variable HOME not found at getUserHomeDir");
	return std::string(home);
}

/**
 * Creates directory name with all parent directories if they aren't exist
 *
 * @param name name of directory to be created
 * @throws std::runtime_error if an error occurred
 */
void createDir(std::string const &name) // throws std::runtime_error
{
	std::string::const_iterator it = name.begin();
	while (it != name.end())
	{
		++it;
		if ( (it == name.end()) || (*it == '/') )
		{
			std::string subname(name.begin(), it);
			//assign USER READ and USER WRITE permissions
			if ( (mkdir(subname.c_str(), S_IRWXU) == -1) && (errno != EEXIST) )
				throw std::runtime_error(getErrorMessage(errno) + " at createDir on " + name);
		}
	}
	errno = 0;
}

void createFile(std::string const &name) //throws std::runtime_error
{
	int fd = open(name.c_str(), O_CREAT, S_IRWXU);
	if (fd == -1)
		throw std::runtime_error(getErrorMessage(errno) + " at createFile on " + name);
	close(fd);
}

void removeFile(std::string const &name) //throws std::runtime_error
{
	if ( unlink( name.c_str() ) == -1 )
		throw std::runtime_error(getErrorMessage(errno) + " at removeFile on " + name);
}

} // namespace utils
