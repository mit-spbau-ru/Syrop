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

#include <boost/algorithm/string.hpp>

#include "selectdialog.h"

typedef std::vector<std::string> strings_t;

SelectDialog::SelectDialog(Glib::ustring const & title)
: Gtk::Dialog   (title, true)
, myLabel       (title)
, myOkButton    ("Ok")
, myCancelButton("Cancel")
, myEntry       (true)
{
	myControlLayout.pack_end(myOkButton,      false, false);
	myControlLayout.pack_end(myCancelButton,  false, false);

	get_vbox()->pack_start(myLabel,         false, true);
	get_vbox()->pack_end  (myControlLayout, false, true);
	get_vbox()->pack_end  (myEntry,         false, true);

	myOkButton.signal_clicked().connect    (sigc::mem_fun(*this,
						&SelectDialog::on_ok_button_clicked
						));
	myCancelButton.signal_clicked().connect(sigc::mem_fun(*this,
						&SelectDialog::on_cancel_button_clicked
						));

	myControlLayout.show_all_children();
	show_all_children();
}

void SelectDialog::setItems(strings_t const & items)
{
	myEntry.remove_all();
	myEntry.get_entry()->set_text(" ");
	for (strings_t::const_iterator it = items.begin(); it != items.end(); ++it)
		myEntry.prepend( Glib::ustring(*it) );
}

std::string SelectDialog::getText() const
{
	return myEntry.get_active_text().raw();
}

void SelectDialog::on_ok_button_clicked()
{
	std::string trimmed( myEntry.get_active_text().raw() );
	boost::trim(trimmed);
	myEntry.set_active_text(trimmed);
	
	if ( !trimmed.empty() ) response(Gtk::RESPONSE_OK);
	else response(Gtk::RESPONSE_CANCEL);
}

void SelectDialog::on_cancel_button_clicked()
{
	response(Gtk::RESPONSE_CANCEL);
}
