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

#ifndef _CORE_SYROP_H_
#define _CORE_SYROP_H_

#include <cstdlib>
#include <unistd.h>
#include <getopt.h>

#include <map>
#include <string>

#include "system.h"
#include "filelocks.h"
#include "coreutils.h"
#include "pluginrunner.h"
#include "proxysettings.h"

using std::string;
using std::vector;
using std::pair;

using core::PluginRunner;
using core::list_plugins;
using core::search_pathes;
using core::application_dir;

using utils::ProxySettings;
using utils::create_dir;
using utils::create_file;
using utils::locked;
using utils::lock;
using utils::unlock;

struct SyropControlArgs
{
	bool apply;
	bool rollback;
	bool create;
	bool help;
	string network;
};

static char const *argsDecsripton = "ca:rh";

static const struct option longOps[] = 
{
	{"create",    no_argument,       NULL, 'c'},
	{"apply",     required_argument, NULL, 'a'},
	{"roll_back", no_argument,       NULL, 'r'},
	{"help",      no_argument,       NULL, 'h'},
	{NULL,        no_argument,       NULL, 0}
};

typedef std::map<std::string, std::string> plugins_t;

#endif // _CORE_SYROP_H_
