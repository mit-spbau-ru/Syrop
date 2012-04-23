#ifndef __GUI_GTK_NEW_NETWORK_DIALOG_H__
#define __GUI_GTK_NEW_NETWORK_DIALOG_H__

#include <gtkmm.h>
#include <string>

class NewNetworkDialog : public Gtk::Dialog
{
public:
	NewNetworkDialog();
	std::string getNetworkName() const;

private:
	Gtk::Label myNetworkLabel;
	Gtk::Entry myNetworkName;
	Gtk::Button myOkButton;
	Gtk::Button myCancelButton;
	Gtk::VBox myMainLayout;
	Gtk::HBox myControlLayout;
	Gtk::HBox myInputLayout;

	void on_ok_clicked();
	void on_cancel_clicked();
};

#endif /*__GUI_GTK_NEW_NETWORK_DIALOG_H__*/
