#ifndef __GUI_GTK_NETWORK_VIEW_H__
#define __GUI_GTK_NETWORK_VIEW_H__

#include <gtkmm.h>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "inidata.h"
#include "applicationview.h"
#include "newnetworkdialog.h"

class NetworkView : public Gtk::VBox
{
public:
	NetworkView    (utils::attributes_map const & map);
	void saveConfig(std::string           const & fname);

private:
	Gtk::Button myRemoveAppButton;
	Gtk::Button myAddAppButton;

	utils::attributes_map myAttributes;
	Gtk::Notebook myPages;
	Gtk::HBox myControl;
	std::vector<boost::shared_ptr<ApplicationView> > myViews;

	NewNetworkDialog myAddDialog;
	
	void on_add_clicked   ();
	void on_remove_clicked();
	void on_dialog_close  (int resp);
};

#endif /*__GUI_GTK_NETWORK_VIEW_H__*/
