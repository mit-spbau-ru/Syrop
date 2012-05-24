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
#include <boost/xpressive/xpressive.hpp>
#include <vector>

#include "mappingdialog.h"

using namespace boost::xpressive;

MappingDialog::MappingDialog()
: Gtk::Dialog   ()
, myOkButton    ("Ok")
, myCancelButton("Cancel")
{
	property_default_height() = 400;
	property_default_width()  = 400;

	myOkButton.signal_clicked().connect    (sigc::mem_fun(*this,
						&MappingDialog::on_ok_button_clicked
						));
	myCancelButton.signal_clicked().connect(sigc::mem_fun(*this,
						&MappingDialog::on_cancel_button_clicked
						));

	myControlLayout.pack_end(myOkButton);
	myControlLayout.pack_end(myCancelButton);
	
	get_vbox()->pack_start(myTextArea,      false, true);
	get_vbox()->pack_end  (myControlLayout, false, true);
	
	myControlLayout.show_all_children();
	show_all_children();
}

void MappingDialog::setContent(utils::attributes const & attrs)
{
	myTextArea.get_buffer()->set_text("");
	for (utils::attributes::const_iterator it = attrs.begin(); it != attrs.end(); ++it)
	{
		myTextArea.get_buffer()->insert(
						myTextArea.get_buffer()->end()
						, Glib::ustring(it->first + "=" + it->second + "\n")
						);
	}
}

void MappingDialog::saveContent(utils::attributes & attrs)
{
	static sregex const attributes = sregex::compile("^\\s*(\\S+){1}\\s*=\\s*(\\S+){1}\\s*$");
	
	Glib::RefPtr<Gtk::TextBuffer> text_buffer = myTextArea.get_buffer();
	std::string text( text_buffer->get_text( text_buffer->begin(), text_buffer->end() ).raw() );
	
	std::vector<std::string> splitVec;
	boost::split(splitVec, text, boost::algorithm::is_any_of("\n"));
	
	for (std::vector<std::string>::const_iterator it = splitVec.begin(); it != splitVec.end(); ++it)
	{
		smatch match;
		if ( regex_match(*it, match, attributes) )
		{
			attrs[match[1].str()] = match[2].str();
		}
	}
}

void MappingDialog::on_ok_button_clicked()
{
	response(Gtk::RESPONSE_OK);
}

void MappingDialog::on_cancel_button_clicked()
{
	response(Gtk::RESPONSE_CANCEL);
}
