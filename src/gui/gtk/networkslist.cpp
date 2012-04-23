#include <algorithm>
#include "networkslist.h"

void NetworkList::init()
{
	Gtk::TreeModelColumnRecord rec;
	rec.add(myColumn);
	myListStore = Gtk::ListStore::create(rec);

	myView.set_model(myListStore);
	myView.append_column("Networks", myColumn);

	myControlLayout.pack_start(myAddButton   , true, true);
	myControlLayout.pack_end  (myRemoveButton, true, true);

	pack_start(myView,          true,  true);
	pack_end  (myControlLayout, false, true);

	myAddButton.signal_clicked().connect   (sigc::mem_fun(*this,
						&NetworkList::on_add_button_clicked
						));
	myRemoveButton.signal_clicked().connect(sigc::mem_fun(*this,
						&NetworkList::on_remove_button_clicked
						));

	myControlLayout.show_all_children();
	show_all_children();
}

NetworkList::NetworkList(std::vector<std::string> const & networks)
: Gtk::VBox     ()
, myAddButton   ("add")
, myRemoveButton("remove")
, myNetworks    (networks)
{
	init();

	for (std::vector<std::string>::const_iterator it = myNetworks.begin();
					it != myNetworks.end(); ++it)
	{
		myListStore->append()->set_value( 0, Glib::ustring(*it) );
	}
}

NetworkList::NetworkList()
: Gtk::VBox     ()
, myAddButton   ("add")
, myRemoveButton("remove")
{
	init();
}

void NetworkList::addNetwork(std::string const & net)
{
	if (std::find(myNetworks.begin(), myNetworks.end(), net) == myNetworks.end())
	{
		myNetworks.push_back(net);
		myListStore->append()->set_value( 0, Glib::ustring(net) );
	}
}

void NetworkList::on_add_button_clicked()
{
}

void NetworkList::on_remove_button_clicked()
{
}
