#ifndef __GUI_GTK_NETWORK_LIST_H__
#define __GUI_GTK_NETWORK_LIST_H__

#include <gtkmm.h>
#include <string>

#include <boost/shared_ptr.hpp>

#include "system.h"
#include "inputdialog.h"
#include "yesnodialog.h"
#include "mappingdialog.h"

class NetworkList : public Gtk::VBox
{
public:
	NetworkList(utils::files_t const &configs);

	sigc::signal<void, std::string const &> signal_added    () const;
	sigc::signal<void, std::string const &> signal_removed  () const;
	sigc::signal<void, std::string const &> signal_activated() const;

	void dropSelection();

private:
	InputDialog myFileDialog;
	YesNoDialog myConfirmDialog;
	MappingDialog myMappingDialog;
	Gtk::Button myAddButton;
	Gtk::Button myRemoveButton;
	Gtk::Button myMappingButton;
	Glib::RefPtr<Gtk::ListStore> myListStore;
	Gtk::TreeView myView;
	Gtk::HBox myControlLayout;

	void on_add_button_clicked   ();
	void on_remove_button_clicked();
	void on_mapping_button_clicked();
	void on_row_activated        (Gtk::TreeModel::Path const & path, Gtk::TreeViewColumn *);

	void change_buttons_state();

	sigc::signal<void, std::string const &> myConfigAddedSignal;
	sigc::signal<void, std::string const &> myConfigRemovedSignal;
	sigc::signal<void, std::string const &> myConfigActivatedSignal;
};

#endif //__GUI_GTK_NETWORK_LIST_H__
