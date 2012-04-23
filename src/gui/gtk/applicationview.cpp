#include <sstream>
#include "applicationview.h"

#define setAttribute(it, ta, tp, map, attr) {                       \
	it = map.find( #attr );                                     \
	if ( it != map.end() )                                      \
	{                                                           \
		bxprs::smatch match;                                \
		if (bxprs::regex_match(it->second,                  \
					match,                      \
					PROXY_REGEX))               \
		{                                                   \
			ta.set_text(match[1].str());                \
			tp.set_text(match[2].str());                \
		}                                                   \
	}                                                           \
}

ApplicationView::ApplicationView(utils::attributes const & attrs)
: Gtk::Grid()
, PROXY_REGEX (bxprs::sregex::compile(REGEX))
, myAttributes(attrs)
, myChangeFlag(false)
, myUseForAll ("same for other protocols")
, myHttpLabel ("http:")
, myHttpsLabel("https:")
, myFtpLabel  ("ftp:")
, mySocksLabel("socks:")
, myHttpPort  (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
, myHttpsPort (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
, myFtpPort   (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
, mySocksPort (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
{
	set_row_spacing(ROWSPACING);
	set_column_spacing(COLSPACING);
	set_border_width(BORDERWIDTH);
	set_resize_mode(Gtk::RESIZE_PARENT);

	myHttpPort.set_numeric(true);
	myHttpsPort.set_numeric(true);
	myFtpPort.set_numeric(true);
	mySocksPort.set_numeric(true);

	utils::attributes::const_iterator it;
	setAttribute(it, myHttpEntry,  myHttpPort,  myAttributes, http);
	setAttribute(it, myHttpsEntry, myHttpsPort, myAttributes, https);
	setAttribute(it, myFtpEntry,   myFtpPort,   myAttributes, ftp);
	setAttribute(it, mySocksEntry, mySocksPort, myAttributes, socks);

	attach(myHttpLabel,   0, 0, 1, 1);
	attach(myHttpEntry,   1, 0, 1, 1);
	attach(myHttpPort,    2, 0, 1, 1);

	attach(myHttpsLabel,  0, 2, 1, 1);
	attach(myHttpsEntry,  1, 2, 1, 1);
	attach(myHttpsPort,   2, 2, 1, 1);

	attach(myFtpLabel,    0, 3, 1, 1);
	attach(myFtpEntry,    1, 3, 1, 1);
	attach(myFtpPort,     2, 3, 1, 1);

	attach(mySocksLabel,  0, 4, 1, 1);
	attach(mySocksEntry,  1, 4, 1, 1);
	attach(mySocksPort,   2, 4, 1, 1);

	attach(myUseForAll,   0, 1, 2, 1);
	myUseForAll.signal_clicked().connect(sigc::mem_fun(*this,
						&ApplicationView::on_check_clicked
					     ));
	myUseForAll.set_active();

	show_all_children();
}
#undef setAttribute

#define getAttribute(ta, tp, map, attr) {                              \
	std::stringstream str;                                         \
	str << ta.get_text().raw() << ":" << tp.get_value_as_int();    \
	map[ #attr ] = str.str();                                      \
}

utils::attributes const & ApplicationView::getAttributes()
{
	getAttribute(myHttpEntry,  myHttpPort,  myAttributes, http);
	if (!myUseForAll.get_active())
	{
		getAttribute(myHttpsEntry, myHttpsPort, myAttributes, https);
		getAttribute(myFtpEntry,   myFtpPort,   myAttributes, ftp);
		getAttribute(mySocksEntry, mySocksPort, myAttributes, socks);
	}
	else
	{
		getAttribute(myHttpEntry,  myHttpPort,  myAttributes, https);
		getAttribute(myHttpEntry,  myHttpPort,  myAttributes, ftp);
		getAttribute(myHttpEntry,  myHttpPort,  myAttributes, socks);
	}

	return myAttributes;
}
#undef getAttribute

void ApplicationView::on_check_clicked()
{
	bool state = !myUseForAll.get_active();

	myHttpsEntry.set_sensitive(state);
	myFtpEntry.set_sensitive  (state);
	mySocksEntry.set_sensitive(state);

	myHttpsPort.set_sensitive (state);
	myFtpPort.set_sensitive   (state);
	mySocksPort.set_sensitive (state);
}
