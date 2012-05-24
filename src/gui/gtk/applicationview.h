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

#ifndef __GUI_GTK_APPLICATION_VIEW_H__
#define __GUI_GTK_APPLICATION_VIEW_H__

#include <boost/xpressive/xpressive.hpp>
#include <gtkmm.h>
#include <string>

#include "inidata.h"

namespace bxprs = boost::xpressive;

class ApplicationView : public Gtk::Grid
{
public:
	ApplicationView(utils::attributes const & attrs);

	bool changed() const;
	void save(utils::IniData & data, std::string const & section);

private:
	std::string   const REGEX;
	bxprs::sregex const PROXY_REGEX;
	bool myChangeFlag;
	
	Gtk::CheckButton myUseForAll;

	Gtk::Label myHttpLabel;
	Gtk::Label myHttpsLabel;
	Gtk::Label myFtpLabel;
	Gtk::Label mySocksLabel;

	Gtk::Entry myHttpEntry;
	Gtk::Entry myHttpsEntry;
	Gtk::Entry myFtpEntry;
	Gtk::Entry mySocksEntry;

	Gtk::SpinButton myHttpPort;
	Gtk::SpinButton myHttpsPort;
	Gtk::SpinButton myFtpPort;
	Gtk::SpinButton mySocksPort;

	void on_check_clicked();
	void on_change();
};

#endif //__GUI_GTK_APPLICATION_VIEW_H__
