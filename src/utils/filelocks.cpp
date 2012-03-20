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

#include <string>
#include <vector>
#include <algorithm>

#include "fileinfo.h"
#include "system.h"

namespace utils
{

typedef std::vector<FileInfo> files_t;

struct Predicat
{
	Predicat(std::string const& s)
	: myValue(s)
	{}
	
	bool operator()(FileInfo const& info) const
	{
		return myValue == info.getName();
	}
	
	std::string myValue;
};

/**
 * Function tests that lock what placed in directory where
 *
 * @param where directory with lock
 * @param what lock name
 * @return true if lock is present and false otherwise
 * @throws std::runtime_error if an error occured
 */
bool locked(std::string const& where, std::string const& what)
{
	files_t const entries = list_dir_entries(where);
	files_t::const_iterator it = find_if(entries.begin(),
						entries.end(), Predicat(what));
	
	return it != entries.end();
}

/**
 * Function tries to place lock what in the dir where
 *
 * @param what lock name
 * @return true if lock is places and false otherwise (if lock already present, for example)
 * @throws std::runtime_error if an error occured
 */
bool lock(std::string const& where, std::string const& what)
{
	if ( !locked(where, what) )
	{
		create_dir(where);
		create_file(where + "/" + what);
		return true;
	}
	return false;
}

/**
 * Function tries to premove lock what from dir where
 *
 * @param what lock name
 * @return true if lock was removed and false otherwise
 * @throws std::runtime_error if an error occured
 */
bool unlock(std::string const& where, std::string const& what)
{
	if ( locked(where, what) )
	{
		remove_file(where + "/" + what);
		return true;
	}
	return false;
}

} // namespace utils
