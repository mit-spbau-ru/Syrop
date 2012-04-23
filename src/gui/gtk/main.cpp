#include <gtkmm.h>
#include "mainwindow.h"

int main(int argc, char **argv)
{
	Gtk::Main kit(argc, argv);
	MainWindow wnd;
	Gtk::Main::run(wnd);
	return 0;
}
