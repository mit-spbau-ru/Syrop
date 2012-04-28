#ifndef __GUI_GTK_NETWORK_VIEW_H__
#define __GUI_GTK_NETWORK_VIEW_H__

#include <gtkmm.h>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include "applicationview.h"
#include "yesnodialog.h"
#include "inputdialog.h"

class NetworkView : public Gtk::VBox
{
public:
	typedef boost::shared_ptr<ApplicationView> view_ptr_t;
	typedef std::map<std::string, view_ptr_t> tabs_t;

	NetworkView(std::string const & name);

	std::string const & getFullName() const;
	void save();

private:
	YesNoDialog mySaveDialog;
	InputDialog myAddDialog;
	std::string myName;
	Gtk::Button myAddButton;
	Gtk::Button myRemoveButton;
	Gtk::Button mySaveButton;
	Gtk::Notebook myApplications;
	Gtk::HBox myControlLayout;
	tabs_t myTabs;

	void on_add_clicked();
	void on_remove_clicked();
	void on_save_clicked();

	void force_save();
	void change_buttons_state();
};

#endif //__GUI_GTK_NETWORK_VIEW_H__
