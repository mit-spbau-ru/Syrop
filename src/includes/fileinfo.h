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

#ifndef _INCLUDES_FILEINFO_H_
#define _INCLUDES_FILEINFO_H_

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace utils {

	/**
	 * System information about file
	 */
	class FileInfo
	{
	public:
		FileInfo(std::string const &name) // throws std::runtime_error
			: myName(name)
		{
			read();
		}
		
		FileInfo()
		{}
	
		/**
		 * Method return only name of file or directory. Example: for file
		 * '/home/mirovingen/aptu', aptu will be returned
		 *
		 * @return file name withot path
		 */
		std::string getName() const
		{
			std::vector<std::string> splitVec;
			boost::split(splitVec, myName, boost::algorithm::is_any_of("/"));
			return splitVec.back();
		}
		
		/**
		 * Method returns full file name
		 *
		 * @return full file name
		 */
		std::string getFullName() const
		{
			return myName;
		}
	
		/**
		 * If file is a directory returns true, otherwise false
		 *
		 * @return true if file is a directory
		 */
		bool isDirectory() const
		{
			return S_ISDIR(myStat.st_mode);
		}
	
		/**
		 * If file is a regular file returns true, otherwise false
		 *
		 * @return true if file is a regular file
		 */
		bool isFile() const
		{
			return S_ISREG(myStat.st_mode);
		}
	
	private:
		std::string myName;
		struct stat myStat;
		
		void read(); // throws std::runtime_error
	};
	
} // namespace utils

#endif //_INCLUDES_FILEINFO_H_
