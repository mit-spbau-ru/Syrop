#include "mainwindow.h"

MainWindow::MainWindow()
: Gtk::Window()
{
	myMainLayout.add2(myNetworksList);
	add(myMainLayout);
	show_all_children();
}
