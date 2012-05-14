#include "inputdialog.h"

InputDialog::InputDialog(Glib::ustring const & title)
: Gtk::Dialog   (title, true)
, myLabel       (title)
, myOkButton    ("Ok")
, myCancelButton("Cancel")
{
	myOkButton.signal_clicked().connect    (sigc::mem_fun(*this,
						&InputDialog::on_ok_button_clicked
						));
	myCancelButton.signal_clicked().connect(sigc::mem_fun(*this,
						&InputDialog::on_cancel_button_clicked
						));

	myControlLayout.pack_end(myOkButton,     false, false);
	myControlLayout.pack_end(myCancelButton, false, false);

	get_vbox()->pack_start(myLabel,         false, true);
	get_vbox()->pack_end  (myControlLayout, false, true);
	get_vbox()->pack_end  (myNetworkName,   false, true);

	myControlLayout.show_all_children();
	show_all_children();
}

std::string InputDialog::getText() const
{
	return myNetworkName.get_text().raw();
}

void InputDialog::on_ok_button_clicked()
{
	response(Gtk::RESPONSE_OK);
}

void InputDialog::on_cancel_button_clicked()
{
	response(Gtk::RESPONSE_CANCEL);
}
