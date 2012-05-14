#include <fstream>
#include <stdexcept>
#include <string>

#include "networkview.h"
#include "iniparser.h"
#include "coreutils.h"

NetworkView::NetworkView(std::string const & name)
: Gtk::VBox     ()
, myChangeFlag  (false)
, mySaveDialog  ("Do you want to save chages?")
, myAddDialog   ("Enter new application name")
, myName        (name)
, myAddButton   ("add")
, myRemoveButton("remove")
, mySaveButton  ("save")
{
	myControlLayout.pack_start(myAddButton,    false, false);
	myControlLayout.pack_start(myRemoveButton, false, false);
	myControlLayout.pack_start(mySaveButton,   false, false);

	std::ifstream in( name.c_str() );
	utils::IniData data;
	in >> data;
	for (utils::IniData::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		view_ptr_t view( new ApplicationView(it->second) );
		myTabs.insert( make_pair(it->first, view) );
		view->show();
		myApplications.append_page(*view, it->first);
	}
	in.close();
	change_buttons_state();

	pack_start(myApplications,  true,  true);
	pack_end  (myControlLayout, false, false);

	myAddButton.signal_clicked().connect   (sigc::mem_fun(*this,
							      &NetworkView::on_add_clicked
							      ));
	myRemoveButton.signal_clicked().connect(sigc::mem_fun(*this,
							      &NetworkView::on_remove_clicked
							      ));
	mySaveButton.signal_clicked().connect  (sigc::mem_fun(*this,
							      &NetworkView::on_save_clicked
							      ));

	myApplications.show_all_children();
	myControlLayout.show_all_children();
	show_all_children();
}

std::string const & NetworkView::getFullName() const
{
	return myName;
}

bool NetworkView::changed() const
{
	return myChangeFlag;
}

void NetworkView::save()
{
	bool flag = changed();
	for (tabs_t::const_iterator it = myTabs.begin(); it != myTabs.end(); ++it)
	{
		if ( flag |= it->second->changed() ) break;
	}
	
	if ( flag && mySaveDialog.run() == Gtk::RESPONSE_YES ) force_save();
	mySaveDialog.hide();
}

void NetworkView::on_add_clicked()
{
	utils::plugins_t plugins;
	utils::list_plugins(utils::search_pathes(), plugins);
	std::vector<std::string> apps;
	for (utils::plugins_t::const_iterator it = plugins.begin(); it != plugins.end(); ++it)
	{
		tabs_t::const_iterator dummy = myTabs.find(it->first);
		if ( dummy == myTabs.end() ) apps.push_back(it->first);
	}
	myAddDialog.setItems(apps);

	if ( myAddDialog.run() == Gtk::RESPONSE_OK )
	{
		view_ptr_t view( new ApplicationView( utils::attributes() ) );
		myTabs.insert( make_pair(myAddDialog.getText(), view) );
		view->show();
		myApplications.prepend_page( *view, myAddDialog.getText() );
		change_buttons_state();
		myApplications.set_current_page(0);
		myChangeFlag = true;
	}
	myAddDialog.hide();
}

void NetworkView::on_remove_clicked()
{
	int current = myApplications.get_current_page();
	if (current >= 0)
	{
		Gtk::Widget * widget = myApplications.get_nth_page( current );
		Glib::ustring label = myApplications.get_tab_label_text( *widget );
		tabs_t::iterator it = myTabs.find( label.raw() );
		if ( it == myTabs.end() ) throw std::logic_error( "Page with label " + label.raw() + " not found" );
		myTabs.erase(it);
		myApplications.remove_page( *widget );
		myApplications.set_current_page(-1);
		change_buttons_state();
		myChangeFlag = true;
	}
}

void NetworkView::on_save_clicked()
{
	force_save();
}

void NetworkView::force_save()
{
	utils::IniData data;
	for (tabs_t::const_iterator it = myTabs.begin(); it != myTabs.end(); ++it)
		it->second->save(data, it->first);
	std::ofstream out( myName.c_str() );
	out << data;
	out.close();
	myChangeFlag = false;
}

void NetworkView::change_buttons_state()
{
	myRemoveButton.set_sensitive(myApplications.get_n_pages() > 0);
}
