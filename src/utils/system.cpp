/*****************************************************************************************
 * Copyright (c) 2012 K. Krasheninnikova, M. Krinkin, S. Martynov, A. Smal, A. Velikiy   *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 *****************************************************************************************/

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
#include "system.h"

namespace utils {

/**
 * Returns error message returned by strerror_r
 *
 * @param errCode error code
 */
std::string error_message(int errCode)
{
	static size_t const maxLen = 256;
	static char msgBuf[maxLen] = {};
	return std::string(strerror_r(errCode, msgBuf, maxLen));
}

/**
 * Function list all directory entries in a directory specified by argument
 *
 * @param dir directory name
 * @param names vector of FileInfo
 * @throws std::runtime_error if an I/O error occured
 */
void list_dir_entries(std::string const &dir, files_t &names) // throws std::runtime_error
{
	DIR *dp = 0;
	dirent *result = 0;
	dirent entry = {};
	
	errno = 0;
	
	if ( ( dp = opendir(dir.c_str()) ) == NULL)
		//if an error occured throw std::runtime_error
		throw std::runtime_error(error_message(errno) + " at listDirEntries on " + dir);
	
	while ( ( readdir_r(dp, &entry, &result) == 0 ) && ( result != NULL ) )
	{
		std::string name(entry.d_name);
		if (name != "." && name != "..")
			names.push_back(FileInfo(dir + "/" + entry.d_name));
	}
	
	//test an error	
	if (errno != 0)
		//throw std::runtime_error if an error occured
		throw std::runtime_error(error_message(errno) + " at listDirEntries on " + dir);
	
	closedir(dp);
}

/**
 * Returns user home dir defined in environment variable HOME
 *
 * @throws std::runtime_error if there isn't variable HOME
 */
std::string user_home_dir() // throws std::runtime_error
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
void create_dir(std::string const &name) // throws std::runtime_error
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
				throw std::runtime_error(error_message(errno) + " at createDir on " + name);
		}
	}
	errno = 0;
}

void create_file(std::string const &name) //throws std::runtime_error
{
	int fd = open(name.c_str(), O_CREAT, S_IRWXU);
	if (fd == -1)
		throw std::runtime_error(error_message(errno) + " at createFile on " + name);
	close(fd);
}

void remove_file(std::string const &name) //throws std::runtime_error
{
	if ( unlink( name.c_str() ) == -1 )
		throw std::runtime_error(error_message(errno) + " at removeFile on " + name);
}

} // namespace utils
