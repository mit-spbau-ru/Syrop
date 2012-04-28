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

