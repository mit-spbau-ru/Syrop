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

#include "pluginrunner.h"

namespace core
{

void PluginRunner::setupSettings(string const &script, AppSettings const &s)
{
	try
	{
		//wrap AppSettings
		wrapper const settings(s);
		//load script
		bpy::object const ignored = bpy::exec_file(bpy::str(script), myMain);
		//find backup function by name
		bpy::object const backup = myMain["backupSettings"];
		//find setupSettings function by name
		bpy::object const setup = myMain["setupSettings"];
		//call
		backup();
		setup(bpy::ptr(&settings));
	}
	catch (bpy::error_already_set const& e)
	{
		PyErr_Print();
	}
}

void PluginRunner::cleanupSettings(string const &script)
{
	try
	{
		bpy::object const ignored = bpy::exec_file(bpy::str(script), myMain);
		bpy::object const cleanup = myMain["cleanupSettings"];
		cleanup();
	}
	catch (bpy::error_already_set const& e)
	{
		PyErr_Print();
	}
}

} // namespace core
