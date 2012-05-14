#include <gtkmm.h>

#include "mainwindow.h"

int main(int argc, char **argv)
{
	Gtk::Main kit(argc, argv);

	utils::files_t configs;
	utils::filter_dir_files(utils::config_dir(), configs);	
	MainWindow wnd(configs);
	wnd.property_default_height().set_value(400);
	wnd.property_default_width().set_value (600);

	Gtk::Main::run(wnd);

	return 0;
}
