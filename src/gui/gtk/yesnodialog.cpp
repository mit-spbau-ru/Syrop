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

#include "yesnodialog.h"

YesNoDialog::YesNoDialog(Glib::ustring const & title)
: Gtk::Dialog(title, true)
, myLabel    (title)
, myYesButton("Yes")
, myNoButton ("No")
{
	myControlLayout.pack_end(myYesButton, false, false);
	myControlLayout.pack_end(myNoButton,  false, false);

	get_vbox()->pack_start(myLabel);
	get_vbox()->pack_end  (myControlLayout);

	myYesButton.signal_clicked().connect(sigc::mem_fun(*this,
							   &YesNoDialog::on_yes_button_clicked
							   ));
	myNoButton.signal_clicked().connect (sigc::mem_fun(*this,
							   &YesNoDialog::on_no_button_clicked
							   ));

	myControlLayout.show_all_children();
	show_all_children();
}

void YesNoDialog::on_yes_button_clicked()
{
	response(Gtk::RESPONSE_YES);
}

void YesNoDialog::on_no_button_clicked()
{
	response(Gtk::RESPONSE_NO);
}

