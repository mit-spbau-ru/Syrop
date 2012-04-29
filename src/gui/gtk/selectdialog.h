#ifndef __GUI_GTK_SELECT_DIALOG_H__
#define __GUI_GTK_SELECT_DIALOG_H__

#include <gtkmm.h>
#include <vector>
#include <string>

class SelectDialog : public Gtk::Dialog
{
public:
	SelectDialog(Glib::ustring const & title);

	void setItems(std::vector<std::string> const & items);
	std::string getText() const;

private:
	Gtk::Label myLabel;
	Gtk::Button myOkButton;
	Gtk::Button myCancelButton;
	Gtk::HBox myControlLayout;
	Gtk::ComboBoxText myEntry;

	void on_ok_button_clicked();
	void on_cancel_button_clicked();	
};

#endif //__GUI_GTK_SELECT_DIALOG_H__
