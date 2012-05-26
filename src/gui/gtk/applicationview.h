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
#include <boost/shared_ptr.hpp>

#include <gtkmm.h>

#include <fstream>
#include <string>
#include <vector>

#include "iniparser.h"
#include "abstractwidget.h"

namespace bxprs = boost::xpressive;

class ApplicationView : public Gtk::VBox
{
public:
	ApplicationView(utils::attributes const & attrs, std::string const & name);

	sigc::signal<void> signal_changed() const { return myChangedSignal; }
	
	void save(utils::IniData & data);

private:
	typedef std::vector<boost::shared_ptr<AbstractWidget> > widgets_t;
	const std::string PROXY_TYPE;
	const std::string TEXT_TYPE;
	const std::string AUTH_TYPE;
	
	std::string myPluginName;
	
	widgets_t myProxyChildren;
	widgets_t myTextChildren;
	widgets_t myAuthChildren;
	
	sigc::signal<void> myChangedSignal;
	
	void loadFields       ( utils::attributes const & attrs, utils::attributes const & fields);
	void loadDefaultFields( utils::attributes const & attrs );
	
	void on_change        () const { myChangedSignal.emit(); }
};

#endif //__GUI_GTK_APPLICATION_VIEW_H__
