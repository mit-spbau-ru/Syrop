#include "networkview.h"
#include "applicationview.h"

NetworkView::NetworkView(utils::attributes_map const & map)
: Gtk::VBox()
, myRemoveAppButton("delete")
, myAddAppButton   ("add")
, myAttributes     (map)
{
	myControl.pack_end(myAddAppButton,    false, false);
	myControl.pack_end(myRemoveAppButton, false, false);

	for (utils::attributes_map::const_iterator it = myAttributes.begin();
					it != myAttributes.end(); ++it)
	{
		boost::shared_ptr<ApplicationView> ptr(new ApplicationView(it->second));
		myViews.push_back(ptr);
		myPages.append_page( *ptr, Glib::ustring(it->first) );
	}

	pack_start(myPages, true, true);
	pack_end(myControl, false, false);

	myAddAppButton.signal_clicked().connect(sigc::mem_fun(*this,
						&NetworkView::on_add_clicked
						));
	myRemoveAppButton.signal_clicked().connect(sigc::mem_fun(*this,
						&NetworkView::on_remove_clicked
						));
	myAddDialog.signal_response().connect(sigc::mem_fun1(*this,
						&NetworkView::on_dialog_close
						));

	show_all_children();
}

void NetworkView::on_add_clicked()
{
	myAddDialog.run();
}

template <typename PtrType>
struct equal
{
	equal(PtrType const & ptr)
	: myPointer(&ptr)
		{}

	template <typename SmartPointer>
	bool operator()(SmartPointer const & sptr) const { return myPointer == sptr.get(); }

	PtrType const * const myPointer;
};

void NetworkView::on_remove_clicked()
{
	int page = myPages.get_current_page();
	equal<ApplicationView> eq(*static_cast<ApplicationView *>(myPages.get_nth_page(page)));
	std::vector<boost::shared_ptr<ApplicationView> >::iterator it = std::find_if(myViews.begin(),
										     myViews.end(),
										     eq);
	if (it != myViews.end())
	{
		boost::shared_ptr<ApplicationView> ptr = *it;
		myViews.erase(it);
		myPages.remove_page(page);
	}
}

void NetworkView::on_dialog_close(int resp)
{
	if (resp && (resp != Gtk::RESPONSE_DELETE_EVENT) ) {
		boost::shared_ptr<ApplicationView> ptr(new ApplicationView(utils::attributes()));
		myViews.push_back(ptr);
		myPages.append_page( *ptr, Glib::ustring(myAddDialog.getNetworkName()) );
		ptr->show();
	}
	myAddDialog.hide();
}

void NetworkView::saveConfig(std::string const & fname)
{
}
