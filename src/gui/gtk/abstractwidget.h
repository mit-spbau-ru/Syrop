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

#ifndef __GUI_GTK_ABSTARCT_WIDGET_H__
#define __GUI_GTK_ABSTARCT_WIDGET_H__

#include <gtkmm.h>
#include <string>

#include "inidata.h"

class AbstractWidget : public Gtk::Box
{
public:
	virtual void save(utils::attributes & data) = 0;
	
	virtual ~AbstractWidget() {}
	
	AbstractWidget(Gtk::Orientation orientation = Gtk::ORIENTATION_HORIZONTAL
			, int spacing = 0)
	: Gtk::Box(orientation, spacing)
		{}

	virtual sigc::signal<void> signal_changed() const { return myChangedSignal; }
	
protected:
	virtual void on_change() const { myChangedSignal.emit(); }
	
private:
	sigc::signal<void> myChangedSignal;
};

#endif //__GUI_GTK_ABSTARCT_WIDGET_H__
