#include <dirent.h>
#include <sys/types.h>

#include <string>
#include <vector>
#include <cerrno>
#include <cstring>

#include "../includes/system.h"

/**
 * Function list all directory entries in a directory specified by argument
 *
 * @param dir directory name
 * @return vector of directory entries names
 * @throws SystemException if an I/O error occured
 */
std::vector<std::string> listDirEntries(const std::string dir)
{
	DIR *dp = 0;
	struct dirent *result = 0;
	struct dirent entry;
	const size_t msglen = 256;
	char msg[msglen];
	std::vector<std::string> names;
	
	if ( ( dp = opendir(dir.c_str()) ) == NULL)
	{
		//if an error occured throw SystemException
		strerror_r(errno, msg, msglen);
		throw SystemException(std::string(msg));
	}
	
	for (int r = readdir_r(dp, &entry, &result); result != NULL && r == 0; r = readdir_r(dp, &entry, &result) )
		names.push_back( std::string(entry.d_name) );
	
	closedir(dp);
	
	//test an error	
	if (errno != 0)
	{
		//throw SystemException if an error occured
		strerror_r(errno, msg, msglen);
		throw SystemException(std::string(msg));
	}
	
	return names;
}