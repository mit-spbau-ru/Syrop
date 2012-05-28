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

#include <sstream>

#include "proxywidget.h"

ProxyWidget::ProxyWidget(std::string const & title, std::string const & value)
: AbstractWidget()
, REGEX         ("^\\s*(\\S+){1}\\s*:\\s*(\\d+){1}\\s*$")
, PROXY_REGEX   (bxprs::sregex::compile(REGEX))
, myLabel       (title.c_str())
, myPort        (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
{
	bxprs::smatch match;
	if ( bxprs::regex_match(value, match, PROXY_REGEX) )
	{
		std::stringstream sstrm;
		int port;
		sstrm << match[2].str();
		sstrm >> port;
		
		myAddress.set_text( match[1].str() );
		myPort.set_value  ( port );
	}

	pack_start( myLabel,   false, false );
	pack_end  ( myPort,    false, false );
	pack_end  ( myAddress, false, true  );
	
	myAddress.signal_changed().connect( sigc::mem_fun(*this, &ProxyWidget::on_change) );
	myPort.signal_changed().connect( sigc::mem_fun(*this, &ProxyWidget::on_change) );
	
	show_all_children();
}

void ProxyWidget::save(utils::attributes & data)
{
	if ( !myAddress.get_text().empty() )
		data[myLabel.get_text().raw()] = myAddress.get_text().raw() + ":" + myPort.get_text().raw();
}
