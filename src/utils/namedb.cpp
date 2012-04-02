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

#include <fstream>
#include <cerrno>

#include "namedb.h"
#include "system.h"
#include "iniparser.h"

namespace utils
{

NamesDataBase::NamesDataBase(std::string const &file)
{
	errno = 0;
	std::ifstream in(file.c_str());
	if ( in.fail() )
		throw std::runtime_error( error_message(errno) );
		
	IniData const data = readData(in);
	in.close();
	
	std::vector<std::string> const names = data.getSectionsList();
	for(std::vector<std::string>::const_iterator it = names.begin(); it != names.end(); ++it)
		readNetworkAttributes(data, *it);
}

#define ADD_ATTRIBUTE(data, it, section, attr) { \
if ( !it->attr.empty() ) \
	data.addAttribute( section, make_pair( #attr, it->attr) ); \
}
void NamesDataBase::write(std::string const &file)
{
	errno = 0;
	std::ofstream out(file.c_str());
	if ( out.fail() )
		throw std::runtime_error( error_message(errno) );
	IniData data;
	for (networks_t::const_iterator it = myBase.begin(); it != myBase.end(); ++it)
	{
		data.addSection(it->config);
		ADD_ATTRIBUTE(data, it, it->config, essid)
		ADD_ATTRIBUTE(data, it, it->config, gwip)
		ADD_ATTRIBUTE(data, it, it->config, netmask)
		ADD_ATTRIBUTE(data, it, it->config, dev)
	}
	
	out << data;
	out.close();
}
#undef ADD_ATTRIBUTE

#define GET_ATTRIBUTE(src, dst, section, attr) { \
if ( src.hasAttribute(section, #attr) ) \
	dst.attr = src.getAttribute(section, #attr); \
}
void NamesDataBase::readNetworkAttributes(IniData const &data, std::string const &network)
{
	NetworkAttributes attr;
	attr.config = network;
	
	GET_ATTRIBUTE(data, attr, network, essid)
	GET_ATTRIBUTE(data, attr, network, gwip)
	GET_ATTRIBUTE(data, attr, network, netmask)
	GET_ATTRIBUTE(data, attr, network, dev)
		
	myBase.push_back(attr);
}
#undef GET_ATTRIBUTE

} // namespace utils
