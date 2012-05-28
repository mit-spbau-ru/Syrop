/*****************************************************************************************
 * Copyright (c) 2012 K. Krasheninnikova, M. Krinkin, S. Martynov, A. Smal, A. Velikiy   *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 *****************************************************************************************/

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

bool MainWindow::on_delete_event(GdkEventAny* event)
{
	if (myLayout.get_child1()) myCurrentNetwork->save();
	return false;
}
