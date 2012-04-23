#ifndef __GUI_GTK_NETWORK_LIST_H__
#define __GUI_GTK_NETWORK_LIST_H__

#include <gtkmm.h>
#include <vector>
#include <string>

class NetworkList : public Gtk::VBox
{
public:
	NetworkList(std::vector<std::string> const & networks);
	NetworkList();

	void addNetwork(std::string const & net);

private:
	Gtk::Button myAddButton;
	Gtk::Button myRemoveButton;
	std::vector<std::string> myNetworks;
	Gtk::TreeModelColumn<Glib::ustring> myColumn;
	Glib::RefPtr<Gtk::ListStore> myListStore;
	Gtk::TreeView myView;
	Gtk::HBox myControlLayout;

	void init();

	void on_add_button_clicked   ();
	void on_remove_button_clicked();
};

#endif /*__GUI_GTK_NETWORK_LIST_H__*/
