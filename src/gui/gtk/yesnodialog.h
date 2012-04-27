#ifndef __GUI_GTK_YES_NO_DIALOG_H__
#define __GUI_GTK_YES_NO_DIALOG_H__

#include <gtkmm.h>

class YesNoDialog : public Gtk::Dialog
{
public:
	YesNoDialog(Glib::ustring const & title);

private:
	Gtk::Label myLabel;
	Gtk::Button myYesButton;
	Gtk::Button myNoButton;
	Gtk::HBox myControlLayout;

	void on_yes_button_clicked();
	void on_no_button_clicked();
};

#endif //__GUI_GTK_YES_NO_DIALOG_H__
