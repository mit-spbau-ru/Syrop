#ifndef __GUI_GTK_APPLICATION_VIEW_H__
#define __GUI_GTK_APPLICATION_VIEW_H__

#include <boost/xpressive/xpressive.hpp>
#include <gtkmm.h>
#include <string>

#include "inidata.h"

namespace bxprs = boost::xpressive;

class ApplicationView : public Gtk::Grid
{
public:
	ApplicationView(utils::attributes const & attrs);

	bool changed() const;
	void save(utils::IniData & data, std::string const & section);

private:
	std::string   const REGEX;
	bxprs::sregex const PROXY_REGEX;
	bool myChangeFlag;
	
	Gtk::CheckButton myUseForAll;

	Gtk::Label myHttpLabel;
	Gtk::Label myHttpsLabel;
	Gtk::Label myFtpLabel;
	Gtk::Label mySocksLabel;

	Gtk::Entry myHttpEntry;
	Gtk::Entry myHttpsEntry;
	Gtk::Entry myFtpEntry;
	Gtk::Entry mySocksEntry;

	Gtk::SpinButton myHttpPort;
	Gtk::SpinButton myHttpsPort;
	Gtk::SpinButton myFtpPort;
	Gtk::SpinButton mySocksPort;

	void on_check_clicked();
	void on_change();
};

#endif //__GUI_GTK_APPLICATION_VIEW_H__
