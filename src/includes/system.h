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

#ifndef _INCLUDES_SYSTEM_H_
#define _INCLUDES_SYSTEM_H_

#include <vector>
#include <string>

#include "fileinfo.h"

namespace utils {
	typedef std::vector<FileInfo> files_t;

	/**
	 * List entries in dir
	 *
	 * @param dir direcotry path
	 * @param names vector of direcotry entries descriptions
	 */
	void list_dir_entries(std::string const &dir, files_t &names);

	/**
	 * Gets .ini files in a directory
	 *
	 * @param dir direcotry path
	 * @param names vector of direcotry entries descriptions
	 */

    void filter_dir_files(std::string const &dir, files_t names);
	
	/**
	 * Returns error message by errcode
	 *
	 * @param errCode error code
	 * @return error message
	 */
	std::string error_message(int errCode);
	
	/**
	 * Return user home directory
	 *
	 * @return user home directory
	 */
	std::string user_home_dir();
	
	/**
	 * Creates directory and all parents
	 *
	 * @param directory path
	 */
	void create_dir(std::string const &name);
	
	/**
	 * Creates an empty file
	 *
	 * @param name file name
	 */
	void create_file(std::string const &name);
	
	/**
	 * Removes specified file
	 *
	 * @param name file name
	 */
	void remove_file(std::string const &name);

} // namespace utils

#endif //_INCLUDES_SYSTEM_H_
