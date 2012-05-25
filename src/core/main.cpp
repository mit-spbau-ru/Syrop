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
#include <iostream>
#include <cerrno>

#include "syrop.h"

void print_usage()
{
	std::cout << "usage:" << std::endl
	          << "\t1. syrop [-c] (-a <network name> | -r) --- apply or roll back proxy parameters" << std::endl
	          << "\t2. syrop -h                            --- print this help" << std::endl << std::endl
		  << "\t\t-c or --create - create config file for network if doesn't exists" << std::endl
		  << "\t\t-a or --apply - apply proxy settings" << std::endl
		  << "\t\t-r or --roll_back" << std::endl;
}

void handle_args(SyropControlArgs const *h)
{
	if ( h->apply && h->rollback )
	{
		std::cerr << "--apply cannot be used with --roll_back" << std::endl;
		exit(1);
	}
	if ( h->apply && h->network.empty() )
	{
		std::cerr << "network name cannot be empty" << std::endl;
		exit(1);
	}
	if ( h->help )
	{
		print_usage();
		exit(1);
	}
	if ( !h->apply && !h->rollback )
	{
		std::cerr << "--apply, --roll_back needed or --help needed" << std::endl;
		exit(1);
	}
}

void parse_args(int argc, char **argv, SyropControlArgs *h)
{
	int c = 0;
	int dummy = 0;
	
	h->apply = h->rollback = h->create = h->help = false;
	
	while ( (c = getopt_long(argc, argv, argsDecsripton, longOps, &dummy) ) != -1 )
	{
		switch (c)
		{
			case 'c':
				h->create = true;
				break;
			case 'a':
				h->apply = true;
				h->network = optarg;
				break;
			case 'r':
				h->rollback = true;
				break;
			case 'h':
			case '?':
			default:
				h->help = true;
				break;
		}
	}
	
	handle_args(h);
}

void apply_parameters(PluginRunner &runner, ProxySettings const& settings)
{
	plugins_t plugins;
	vector<string> const& pathes = search_pathes();
	list_plugins(pathes, plugins);
	
	for (plugins_t::const_iterator it = plugins.begin(); it != plugins.end(); ++it)
		runner.setupSettings( it->second + "/" + it->first
					+ utils::PLUGIN_EXTENSION
					, settings[it->first] );
}

void cancel_parameters(PluginRunner &runner)
{
	plugins_t plugins;
	vector<string> const& pathes = search_pathes();
	list_plugins(pathes, plugins);
	
	for (plugins_t::const_iterator it = plugins.begin(); it != plugins.end(); ++it)
		runner.cleanupSettings( it->second + "/" + it->first
					+ utils::PLUGIN_EXTENSION );
}

int main(int argc, char **argv)
{	
	try
	{
		SyropControlArgs handleParams = {};
		parse_args(argc, argv, &handleParams);
		string const appDir = application_dir();
		PluginRunner runner;
		ProxySettings settings;
	
		//call plugins
		if ( handleParams.apply )
		{
			string const configDir = appDir + utils::CONFIGS;
			string const configName = configDir + handleParams.network;
			if ( handleParams.create )
			{
				//create proxy config file if dosen't exists
				create_dir(configDir);
				create_file(configName);
			}
			settings.load(configName);
			apply_parameters(runner, settings);
		}
		//roll back settings
		else if ( handleParams.rollback )
		{
			cancel_parameters(runner);
		}
	}
	catch (std::runtime_error const& e)
	{
		std::cerr << "error: " << e.what() << std::endl;
		return 1;
	}
	catch (std::exception const& e)
	{
		std::cerr << "unexpected exception: " << e.what() << std::endl;
		return 1;
	}
	
	return EXIT_SUCCESS;
}
