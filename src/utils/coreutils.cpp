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

#include <exception>

#include "system.h"
#include "coreutils.h"
#include "fileinfo.h"

using std::make_pair;

namespace utils
{

static bool test_plugin(FileInfo const &info)
{
	//plugin is a direcotiry with a python script
	if (info.isDirectory())
	{
		//list files
		files_t const children = list_dir_entries(info.getFullName());
		for (files_t::const_iterator it = children.begin(); it != children.end(); ++it)
			if (it->getName() == (info.getName() + PLUGIN_EXTENSION) )
				//main plugin file must have same name as plugin directory
				return true;
	}
	return false;
}

//function adds plugins in a specified directory to map
static void list_plugins(string const &dir, plugins_t &plugins)
{
	files_t const children = list_dir_entries(dir);
	for (files_t::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		if (test_plugin(*it))
			plugins[it->getName()] = it->getFullName() + "/" + it->getName() + PLUGIN_EXTENSION;
	}
}

/**
 * Function returns syrop directory in user home, if directory dosen't
 * exists function creates it
 */
std::string const& application_dir()
{
	static string const dirName(user_home_dir() + "/" + HOME);
	create_dir(dirName);
	return dirName;
}

/**
 * Returns vector of standard path for searching plugins:
 *  %HOME%/.syrop/plugins
 *  /usr/share/syrop/plugins
 */
vector<string> const& search_pathes()
{
	static vector<string> pathes;
	if (pathes.empty())
	{
		try
		{
			FileInfo info(user_home_dir() + "/" + HOME + PLUGINS);
			pathes.push_back(info.getFullName());
		}
		catch (std::runtime_error const &e)
		{}
		
		try
		{
			FileInfo info(SETUP + PLUGINS);
			pathes.push_back(info.getFullName());
		}
		catch (std::runtime_error const &e)
		{}
	}
	return pathes;
}

/**
 * List plugins in directories specified by pathes
 */
void list_plugins(vector<string> const& pathes, plugins_t &plugins)
{
	//for every path in a vector
	for (vector<string>::const_iterator it = pathes.begin(); it != pathes.end(); ++it)
		list_plugins(*it, plugins);
}

} // namespace utils
