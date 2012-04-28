#include <sstream>

#include "applicationview.h"

ApplicationView::ApplicationView(utils::attributes const & attrs)
: Gtk::Grid   ()
, REGEX       ("^\\s*(\\S+){1}\\s*:\\s*(\\d+){1}\\s*$")
, PROXY_REGEX (bxprs::sregex::compile(REGEX))
, myUseForAll ("same for other protocols")
, myHttpLabel ("HTTP:")
, myHttpsLabel("HTTP:")
, myFtpLabel  ("FTP:")
, mySocksLabel("SOCKS:")
, myHttpPort  (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
, myHttpsPort (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
, myFtpPort   (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
, mySocksPort (Gtk::Adjustment::create(3128, 1, 65000, 1, 10, 0))
{
	for (utils::attributes::const_iterator it = attrs.begin(); it != attrs.end(); ++it)
	{
		bxprs::smatch match;
		if ( bxprs::regex_match(it->second, match, PROXY_REGEX) )
		{
			std::stringstream str;
			int port;
			str << match[2].str();
			str >> port;
			if (it->first == "http")
			{
				myHttpEntry.set_text ( match[1].str() );
				myHttpPort.set_value ( port );
			}
			else if (it->first == "https")
			{
				myHttpsEntry.set_text( match[1].str() );
				myHttpsPort.set_value( port );
			}
			else if (it->first == "ftp")
			{
				myFtpEntry.set_text  ( match[1].str() );
				myFtpPort.set_value  ( port );
			}
			else if (it->first == "socks")
			{
				mySocksEntry.set_text( match[1].str() );
				mySocksPort.set_value( port );
			}
		}
	}

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
	myUseForAll.set_active(false);

	show_all_children();
}

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

void ApplicationView::save(utils::IniData & data, std::string const & section) const
{
	data.addSection(section);
	std::string value(myHttpEntry.get_text().raw() + ":" + myHttpPort.get_text().raw());
	data.addAttribute( section, make_pair( std::string("http"), value ) );


	if ( !myUseForAll.get_active() )
	{
		value = myHttpsEntry.get_text().raw() + ":" + myHttpsPort.get_text().raw();
		data.addAttribute( section, make_pair( std::string("https"), value ) );

		value = myFtpEntry.get_text().raw() + ":" + myFtpPort.get_text().raw();
		data.addAttribute( section, make_pair( std::string("ftp"), value ) );

		value = mySocksEntry.get_text().raw() + ":" + mySocksPort.get_text().raw();
		data.addAttribute( section, make_pair( std::string("socks"), value ) );
	}
	else
	{
		data.addAttribute( section, make_pair( std::string("https"), value ) );
		data.addAttribute( section, make_pair( std::string("ftp"), value ) );
		data.addAttribute( section, make_pair( std::string("socks"), value ) );
	}
}
