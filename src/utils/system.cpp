#include <dirent.h>
#include <sys/types.h>

#include <string>
#include <vector>
#include <cerrno>
#include <cstring>

#include "../includes/system.h"

namespace utils {

/**
 * Function list all directory entries in a directory specified by argument
 *
 * @param dir directory name
 * @return vector of directory entries names
 * @throws SystemException if an I/O error occured
 */
std::vector<std::string> listDirEntries(std::string const &dir) throw(SystemException)
{
	DIR *dp = 0;
	struct dirent *result = 0;
	struct dirent entry;
	const size_t msglen = 256;
	char msg[msglen];
	std::vector<std::string> names;
	
	if ( ( dp = opendir(dir.c_str()) ) == NULL)
		//if an error occured throw SystemException
		throw SystemException(std::string(strerror_r(errno, msg, msglen)));
	
	for (int r = readdir_r(dp, &entry, &result); result != NULL && r == 0; r = readdir_r(dp, &entry, &result) )
		names.push_back( std::string(entry.d_name) );
	
	closedir(dp);
	
	//test an error	
	if (errno != 0)
		//throw SystemException if an error occured
		throw SystemException(std::string(strerror_r(errno, msg, msglen)));
	
	return names;
}


/**
 * Function gets FileInfo for a file specified by name argument
 *
 * @param name file name
 * @return FileInfo for file specified by name
 * @throws SystemException if an stat system call error occured
 */
FileInfo getFileInfo(std::string const &name) throw(SystemException)
{
	FileInfo info(name);
	info.read();
	
	return info;
}

} // namespace utils