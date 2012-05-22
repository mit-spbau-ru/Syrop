#include <fstream>

#include "networkslist.h"
#include "coreutils.h"
#include "iniparser.h"

NetworkList::NetworkList(utils::files_t const &configs)
: Gtk::VBox      ()
, myFileDialog   ("Enter new profile name")
, myConfirmDialog("Are you really want to delete this network?")
, myAddButton    ("add")
, myRemoveButton ("remove")
, myMappingButton("mapping")
{
	Gtk::TreeModelColumn<Glib::ustring> nameColumn;
	Gtk::TreeModelColumn<Glib::ustring> pathColumn;
	Gtk::TreeModelColumnRecord record;
	record.add(nameColumn);
	record.add(pathColumn);

	myListStore = Gtk::ListStore::create(record);
	myView.set_model(myListStore);
	myView.append_column("Networks", nameColumn);

	myControlLayout.pack_end(myMappingButton, true, true);
	myControlLayout.pack_end(myRemoveButton,  true, true);
	myControlLayout.pack_end(myAddButton,     true, true);

	pack_start(myView,          true,  true);
	pack_end  (myControlLayout, false, true);

	myAddButton.signal_clicked().connect   (sigc::mem_fun(*this,
						&NetworkList::on_add_button_clicked
						));
	myRemoveButton.signal_clicked().connect(sigc::mem_fun(*this,
						&NetworkList::on_remove_button_clicked
						));
	myMappingButton.signal_clicked().connect(sigc::mem_fun(*this,
						&NetworkList::on_mapping_button_clicked
						));
	myView.signal_row_activated().connect(sigc::mem_fun(*this,
						&NetworkList::on_row_activated
						));

	for (utils::files_t::const_iterator it = configs.begin(); it != configs.end(); ++it)
	{
		Gtk::ListStore::iterator place = myListStore->append();
		place->set_value(0, Glib::ustring( it->getName() ));
		place->set_value(1, Glib::ustring( it->getFullName() ));
	}
	change_buttons_state();
	myControlLayout.show_all_children();
	show_all_children();
}

void NetworkList::on_add_button_clicked()
{
	if (myFileDialog.run() == Gtk::RESPONSE_OK)
	{
		std::string fullName( utils::config_dir() + "/" + myFileDialog.getText() );
		utils::create_file( fullName);
		utils::FileInfo conf( fullName );

		Gtk::ListStore::iterator place = myListStore->append();
		place->set_value(0, conf.getName() );
		place->set_value(1, conf.getFullName() );
		change_buttons_state();
	}
	myFileDialog.hide();
}

void NetworkList::on_remove_button_clicked()
{
	Gtk::ListStore::iterator it = myView.get_selection()->get_selected();
	if ( it && (myConfirmDialog.run() == Gtk::RESPONSE_YES) )
	{
		Glib::ustring fullName;
		it->get_value(1, fullName);
		myConfigRemovedSignal.emit( fullName.raw() );
		myListStore->erase(it);
		utils::remove_file( fullName.raw() );
		change_buttons_state();
	}
	myConfirmDialog.hide();
}

void NetworkList::on_mapping_button_clicked()
{
	static const std::string mappingFile( utils::application_dir() + "/mappings.conf" );
	
	Gtk::ListStore::iterator it = myView.get_selection()->get_selected();
	if ( it )
	{
		Glib::ustring name;
		it->get_value(0, name);
		myMappingDialog.set_title( name.raw() );
		
		utils::IniData data;
		std::ifstream in( mappingFile.c_str() );
		in >> data;
		in.close();
		myMappingDialog.setContent(data[name]);
	
		if (myMappingDialog.run() == Gtk::RESPONSE_OK)
		{
			myMappingDialog.saveContent(data[name]);
			std::ofstream out( mappingFile.c_str() );
			out << data;
			out.close();
		}
		myMappingDialog.hide();
	}
}

void NetworkList::on_row_activated(Gtk::TreeModel::Path const & path, Gtk::TreeViewColumn *)
{
	Gtk::ListStore::const_iterator it = myListStore->get_iter(path);
	if ( it )
	{
		Glib::ustring fullName;
		it->get_value(1, fullName);
		myConfigActivatedSignal.emit( fullName.raw() ); 
	}
}

sigc::signal<void, std::string const &> NetworkList::signal_added() const
{
	return myConfigAddedSignal;
}

sigc::signal<void, std::string const &> NetworkList::signal_removed() const
{
	return myConfigRemovedSignal;
}

sigc::signal<void, std::string const &> NetworkList::signal_activated() const
{
	return myConfigActivatedSignal;
}

void NetworkList::dropSelection()
{
	Gtk::ListStore::Row row = myListStore->children()[0];
	if (row) myView.get_selection()->select(row);
}

void NetworkList::change_buttons_state()
{
	myRemoveButton.set_sensitive( myListStore->children().size() > 0 );
}
