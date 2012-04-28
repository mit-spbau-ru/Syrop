#ifndef __GUI_GTK_MAIN_WINDOW_H__
#define __GUI_GTK_MAIN_WINDOW_H__

#include <boost/shared_ptr.hpp>
#include <string>
#include <gtkmm.h>

#include "networkslist.h"
#include "networkview.h"
#include "coreutils.h"

class MainWindow : public Gtk::Window
{
public:
	MainWindow(utils::files_t const &configs);

private:
	NetworkList myNetworks;
	boost::shared_ptr<NetworkView> myCurrentNetwork;
	Gtk::HPaned myLayout;

	void on_network_add     (std::string const &name);
	void on_network_delete  (std::string const &name);
	void on_network_selected(std::string const &name);
};

#endif //__GUI_GTK_MAIN_WINDOW_H__
