#ifndef __GUI_GTK_MAIN_WINDOW_H__
#define __GUI_GTK_MAIN_WINDOW_H__

#include <gtkmm.h>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "networkslist.h"
#include "networkview.h"

class MainWindow : public Gtk::Window
{
public:
	MainWindow();

private:
	Gtk::HPaned myMainLayout;
	std::vector<boost::shared_ptr<NetworkView> > myNetworksViews;
	NetworkList myNetworksList;
};

#endif /*__GUI_GTK_MAIN_WINDOW_H__*/
