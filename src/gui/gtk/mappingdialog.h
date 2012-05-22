#ifndef __GUI_GTK_MAPPING_DIALOG_H__
#define __GUI_GTK_MAPPING_DIALOG_H__

#include <string>
#include <gtkmm.h>

#include "inidata.h"

class MappingDialog : public Gtk::Dialog
{
public:
	MappingDialog();
	
	void setContent(utils::attributes const & attrs);
	void saveContent(utils::attributes & attrs);

private:
	Gtk::Button myOkButton;
	Gtk::Button myCancelButton;
	Gtk::HBox myControlLayout;
	Gtk::TextView myTextArea;
	
	void on_ok_button_clicked();
	void on_cancel_button_clicked();
};

#endif // __GUI_GTK_MAPPING_DIALOG_H__
