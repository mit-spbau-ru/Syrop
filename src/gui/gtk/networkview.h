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

#ifndef __GUI_GTK_NETWORK_VIEW_H__
#define __GUI_GTK_NETWORK_VIEW_H__

#include <gtkmm.h>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include "applicationview.h"
#include "yesnodialog.h"
#include "selectdialog.h"

class NetworkView : public Gtk::VBox
{
public:
	typedef boost::shared_ptr<ApplicationView> view_ptr_t;
	typedef std::map<std::string, view_ptr_t> tabs_t;

	NetworkView(std::string const & name);

	std::string const & getFullName() const;
	void save();

private:
	bool myChangeFlag;
	YesNoDialog mySaveDialog;
	SelectDialog myAddDialog;
	std::string myName;
	Gtk::Button myAddButton;
	Gtk::Button myRemoveButton;
	Gtk::Button mySaveButton;
	Gtk::Notebook myApplications;
	Gtk::HBox myControlLayout;
	tabs_t myTabs;

	void on_add_clicked();
	void on_remove_clicked();
	void on_save_clicked();

	void force_save();
	void changed();
	void change_buttons_state();
};

#endif //__GUI_GTK_NETWORK_VIEW_H__
