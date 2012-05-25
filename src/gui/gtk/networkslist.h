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

#ifndef __GUI_GTK_NETWORK_LIST_H__
#define __GUI_GTK_NETWORK_LIST_H__

#include <gtkmm.h>
#include <string>

#include <boost/shared_ptr.hpp>

#include "system.h"
#include "inputdialog.h"
#include "yesnodialog.h"
#include "mappingdialog.h"
#include "iniparser.h"

class NetworkList : public Gtk::VBox
{
public:
	NetworkList(utils::files_t const &configs);

	sigc::signal<void, std::string const &> signal_added    () const;
	sigc::signal<void, std::string const &> signal_removed  () const;
	sigc::signal<void, std::string const &> signal_activated() const;

	void dropSelection();

private:
	InputDialog myFileDialog;
	YesNoDialog myConfirmDialog;
	MappingDialog myMappingDialog;
	Gtk::Button myAddButton;
	Gtk::Button myRemoveButton;
	Gtk::Button myMappingButton;
	Glib::RefPtr<Gtk::ListStore> myListStore;
	Gtk::TreeView myView;
	Gtk::HBox myControlLayout;

	void on_add_button_clicked   ();
	void on_remove_button_clicked();
	void on_mapping_button_clicked();
	void on_row_activated        (Gtk::TreeModel::Path const & path, Gtk::TreeViewColumn *);

	void change_buttons_state();
	void loadIniData(utils::IniData &data) const;
	void saveIniData(utils::IniData const &data) const;

	sigc::signal<void, std::string const &> myConfigAddedSignal;
	sigc::signal<void, std::string const &> myConfigRemovedSignal;
	sigc::signal<void, std::string const &> myConfigActivatedSignal;
};

#endif //__GUI_GTK_NETWORK_LIST_H__
