#include "mainwindow.h"

MainWindow::MainWindow(utils::files_t const &configs)
: Gtk::Window     ()
, myNetworks      (configs)
{
	myLayout.pack2(myNetworks, true, true);
	add(myLayout);

	myNetworks.signal_added().connect    (sigc::mem_fun(*this,
					      &MainWindow::on_network_add
					      ));
	myNetworks.signal_removed().connect  (sigc::mem_fun(*this,
					      &MainWindow::on_network_delete
					      ));
	myNetworks.signal_activated().connect(sigc::mem_fun(*this,
					      &MainWindow::on_network_selected
					      ));

	myNetworks.dropSelection();
	show_all_children();
}

void MainWindow::on_network_add(std::string const &name)
{
	on_network_selected(name);
}

void MainWindow::on_network_delete(std::string const &name)
{
	if (myCurrentNetwork && myCurrentNetwork->getFullName() == name)
	{
		myLayout.remove( *myLayout.get_child1() );
		myCurrentNetwork.reset();
	}
}

void MainWindow::on_network_selected(std::string const &name)
{
	if ( myLayout.get_child1() && myCurrentNetwork->getFullName() != name )
	{
		myCurrentNetwork->save();
		myLayout.remove( *myLayout.get_child1() );
	}
	myCurrentNetwork.reset( new NetworkView(name) );
	myLayout.pack1(*myCurrentNetwork, true, true);
	myCurrentNetwork->show();
}
