#ifndef __GUI_GTK_NEW_FILE_DIALOG_H__
#define __GUI_GTK_NEW_FILE_DIALOG_H__

#include <gtkmm.h>

class InputDialog : public Gtk::Dialog
{
public:
	InputDialog(Glib::ustring const & title);
	std::string getText() const;
	
private:
	Gtk::Button myOkButton;
	Gtk::Button myCancelButton;
	Gtk::Label myLabel;
	Gtk::Entry myNetworkName;
	Gtk::HBox myControlLayout;

	void on_ok_button_clicked();
	void on_cancel_button_clicked();
};

#endif //__GUI_GTK_NEW_FILE_DIALOG_H__
