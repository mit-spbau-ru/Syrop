#ifndef __GUI_GTK_APPLICATION_VIEW_H__
#define __GUI_GTK_APPLICATION_VIEW_H__

#include <boost/xpressive/xpressive.hpp>
#include <gtkmm.h>
#include "inidata.h"

#define ROWSPACING   5
#define COLSPACING   5
#define BORDERWIDTH  2
#define REGEX        "^\\s*(\\S+){1}\\s*:\\s*(\\d+){1}\\s*$"

namespace bxprs = boost::xpressive;

class ApplicationView : public Gtk::Grid
{
public:
	ApplicationView(utils::attributes const& attrs);
	utils::attributes const & getAttributes();

private:
	bxprs::sregex const PROXY_REGEX;

	utils::attributes myAttributes;
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
};

#endif /*__GUI_GTK_APPLICATION_VIEW_H__*/
