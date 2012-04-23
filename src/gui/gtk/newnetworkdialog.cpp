#include "newnetworkdialog.h"

NewNetworkDialog::NewNetworkDialog()
: Gtk::Dialog   ("New network")
, myNetworkLabel("Network:")
, myOkButton    ("Ok")
, myCancelButton("Cancel")
{
	myControlLayout.pack_end(myOkButton,      false, false);
	myControlLayout.pack_end(myCancelButton,  false, false);

	myInputLayout.pack_start(myNetworkLabel,  false, false);
	myInputLayout.pack_end  (myNetworkName,   true,  false);

	get_vbox()->pack_start  (myInputLayout,   true,  false);
	get_vbox()->pack_end    (myControlLayout, true,  false);

	myOkButton.signal_clicked().connect(sigc::mem_fun(*this,
					    &NewNetworkDialog::on_ok_clicked
					    ));
	myCancelButton.signal_clicked().connect(sigc::mem_fun(*this,
					    &NewNetworkDialog::on_cancel_clicked
					    ));

	show_all_children();
}

std::string NewNetworkDialog::getNetworkName() const
{
	return myNetworkName.get_text().raw();
}

void NewNetworkDialog::on_ok_clicked()
{
	response(1);
}

void NewNetworkDialog::on_cancel_clicked()
{
	response(0);
}
