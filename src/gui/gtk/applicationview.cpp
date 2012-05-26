/*****************************************************************************************
 * Copyright (c) 2012 K. Krasheninnikova, M. Krinkin, S. Martynov, A. Smal, A. Velikiy   *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 *****************************************************************************************/

#include "applicationview.h"
#include "coreutils.h"

#include "proxywidget.h"
#include "authwidget.h"
#include "textwidget.h"

ApplicationView::ApplicationView(utils::attributes const & attrs, std::string const & name)
: Gtk::VBox   ()
, PROXY_TYPE  ("proxy")
, TEXT_TYPE   ("text")
, AUTH_TYPE   ("auth")
, myPluginName(name)
{
	utils::plugins_t plugins;
	utils::list_plugins(utils::search_pathes(), plugins);
	utils::plugins_t::const_iterator it = plugins.find(myPluginName);
	if ( it != plugins.end() )
	{
		std::string fieldsFileName(it->second + "/" + utils::FIELDS_FILE);
		std::ifstream input( fieldsFileName.c_str() );
		if ( input.is_open() )
		{
			utils::IniData data;
			input >> data;
			for (utils::IniData::const_iterator iit = data.begin(); iit != data.end(); ++iit)
				if ( iit->first == "fields" ) loadFields(attrs, iit->second);
			input.close();
		}
	}
	if ( myProxyChildren.empty() && myTextChildren.empty() && myAuthChildren.empty() )
		loadDefaultFields(attrs);
	
	for (widgets_t::const_iterator iit = myProxyChildren.begin(); iit != myProxyChildren.end(); ++iit)
		pack_start(**iit, false, true);
		
	for (widgets_t::const_iterator iit = myTextChildren.begin(); iit != myTextChildren.end(); ++iit)
		pack_start(**iit, false, true);
		
	for (widgets_t::const_iterator iit = myAuthChildren.begin(); iit != myAuthChildren.end(); ++iit)
		pack_start(**iit, false, true);

	show_all_children();
}

void ApplicationView::loadFields(utils::attributes const & attrs, utils::attributes const & fields)
{
	for (utils::attributes::const_iterator it = fields.begin(); it != fields.end(); ++it)
	{
		std::string const & title = it->first;
		std::string const & type  = it->second;
		boost::shared_ptr<AbstractWidget> widget;
		
		std::string value;
		utils::attributes::const_iterator it = attrs.find(title);
		if ( it != attrs.end() ) value = it->second;

		if (type == PROXY_TYPE)
		{
			widget.reset( new ProxyWidget(title, value) );
			myProxyChildren.push_back(widget);
		}
		else if (type == AUTH_TYPE)
		{
			widget.reset( new AuthWidget(title, value) );
			myTextChildren.push_back(widget);
		}
		else
		{
			widget.reset( new TextWidget(title, value) );
			myAuthChildren.push_back(widget);
		}
		
		widget->signal_changed().connect( sigc::mem_fun(*this, &ApplicationView::on_change) );
	}
}

void ApplicationView::loadDefaultFields(utils::attributes const & attrs)
{
	boost::shared_ptr<AbstractWidget> widget;
	std::string value;
	
	utils::attributes::const_iterator it = attrs.find("http");
	if ( it != attrs.end() ) value = it->second;
	widget.reset( new ProxyWidget("http", value) );
	widget->signal_changed().connect( sigc::mem_fun(*this, &ApplicationView::on_change) );
	myProxyChildren.push_back(widget);

	it = attrs.find("https");
	if ( it != attrs.end() ) value = it->second;
	widget.reset( new ProxyWidget("https", value) );
	widget->signal_changed().connect( sigc::mem_fun(*this, &ApplicationView::on_change) );
	myProxyChildren.push_back(widget);

	it = attrs.find("ftp");
	if ( it != attrs.end() ) value = it->second;
	widget.reset( new ProxyWidget("ftp", value) );
	widget->signal_changed().connect( sigc::mem_fun(*this, &ApplicationView::on_change) );
	myProxyChildren.push_back(widget);

	it = attrs.find("socks");
	if ( it != attrs.end() ) value = it->second;
	widget.reset( new ProxyWidget("socks", value) );
	widget->signal_changed().connect( sigc::mem_fun(*this, &ApplicationView::on_change) );
	myProxyChildren.push_back(widget);
}

void ApplicationView::save(utils::IniData & data)
{
	utils::attributes attrs;
	
	for (widgets_t::const_iterator it = myProxyChildren.begin(); it != myProxyChildren.end(); ++it)
		(*it)->save(attrs);
		
	for (widgets_t::const_iterator it = myTextChildren.begin(); it != myTextChildren.end(); ++it)
		(*it)->save(attrs);
		
	for (widgets_t::const_iterator it = myAuthChildren.begin(); it != myAuthChildren.end(); ++it)
		(*it)->save(attrs);
		
	data[myPluginName] = attrs;
}
