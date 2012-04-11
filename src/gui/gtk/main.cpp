#include <gtkmm/window.h>
#include <libglademm/xml.h>
#include <gtkmm.h>
#include <iostream>

#define _DEBUG

#ifdef _DEBUG
#define RCDIR "rc/"
#else
#define RCDIR "/usr/share/syrop/gtk/rc/"
#endif

#define UIFILE "syrop-ui.glade"
#define UIPATH RCDIR UIFILE

struct AppContext
{
	Gtk::Window * mainWindow;
	Gtk::Dialog * aboutDialog;

	AppContext(Glib::RefPtr<Gtk::Builder> builder)
	{
		builder->get_widget("mainWindow", mainWindow);
		builder->get_widget("aboutDialog", aboutDialog);
		
		Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object("aboutAction"))->signal_activate()
			.connect( sigc::mem_fun(this, &AppContext::aboutActionActivate) );
		Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object("quitAction"))->signal_activate()
			.connect( sigc::mem_fun(this, &AppContext::quitActionActivate) );
		Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object("saveAction"))->signal_activate()
			.connect( sigc::mem_fun(this, &AppContext::saveActionActivate) );
		Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object("addAction"))->signal_activate()
			.connect( sigc::mem_fun(this, &AppContext::addActionActivate) );
		Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object("removeAction"))->signal_activate()
			.connect( sigc::mem_fun(this, &AppContext::removeActionActivate) );

		aboutDialog->signal_response().connect(sigc::mem_fun(this, &AppContext::aboutDialogResponse));
	}

	int run()
	{
		Gtk::Main::run(*mainWindow);
		return EXIT_SUCCESS;
	}

	virtual ~AppContext()
	{
		delete mainWindow;
		delete aboutDialog;
	}

	void aboutActionActivate()
	{
		aboutDialog->run();
	}

	void quitActionActivate()
	{
		mainWindow->hide();
	}

	void saveActionActivate()
	{
		//TODO: implement	
	}

	void addActionActivate()
	{
		//TODO: implement
	}

	void removeActionActivate()
	{
		//TODO: implement
	}

	void aboutDialogResponse(int)
	{
		aboutDialog->hide();
	}
};

int main(int argc, char **argv)
{
	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> refXml;
	try
	{
		AppContext app(Gtk::Builder::create_from_file(UIPATH));
		return app.run();
	}
	catch(const Glib::Exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
