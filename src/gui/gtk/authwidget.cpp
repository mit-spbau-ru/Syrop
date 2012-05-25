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

#include "authwidget.h"

AuthWidget::AuthWidget(std::string const & title, std::string const & value)
: AbstractWidget (Gtk::ORIENTATION_VERTICAL)
, REGEX_STRING   ("^\\s*(\\S+){1}\\s*:\\s*(\\S+){1}\\s*$")
, REGEX          (bxprs::sregex::compile(REGEX_STRING))
, myTitle        (title)
, myUserLabel    ("user")
, myPasswordLabel("password")
, myShowPassword ("show password")
{
	bxprs::smatch match;
	if ( bxprs::regex_match(value, match, REGEX) )
	{	
		myUserEntry.set_text    ( match[1].str() );
		myPasswordEntry.set_text( match[2].str() );
	}
	
	myShowPassword.set_active(false);
	myPasswordEntry.set_visibility(false);
	myPasswordEntry.set_invisible_char('*');
	
	myShowPassword.signal_clicked().connect( sigc::mem_fun(*this, &AuthWidget::show_password_clicked) );
	myUserEntry.signal_changed().connect( sigc::mem_fun(*this, &AuthWidget::on_change) );
	myPasswordEntry.signal_changed().connect( sigc::mem_fun(*this, &AuthWidget::on_change) );
	
	myUserLayout.pack_start( myUserLabel, false, false );
	myUserLayout.pack_end  ( myUserEntry, false, true  );
	
	myPasswordLayout.pack_start( myPasswordLabel, false, false );
	myPasswordLayout.pack_end  ( myPasswordEntry, false, true  );
	
	pack_start( myUserLayout,     false, true );
	pack_start( myPasswordLayout, false, true );
	pack_start( myShowPassword,   false, true );
	
	myUserLayout.show_all_children();
	myPasswordLayout.show_all_children();
	show_all_children();
}

void AuthWidget::show_password_clicked()
{
	myPasswordEntry.set_visibility( myShowPassword.get_active() );
}

void AuthWidget::save(utils::attributes & data)
{
	data[myTitle] = myUserEntry.get_text().raw() + ":" + myPasswordEntry.get_text().raw();
	on_save();
}
