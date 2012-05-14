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

#ifndef _INCLUDES_PROXYSETTINGS_
#define _INCLUDES_PROXYSETTINGS_

#include "inidata.h"
#include "iniparser.h"

namespace utils{

	
	class ProxySettings
	{
	public:
        ProxySettings() {}

        ProxySettings( string const &fileName )
		{
			load( fileName );
		}
		
        void load               ( string const &fileName );
        void save               ( string const &fileName )      const;
        bool exists             ( const std::string& appName )  const;
        void remove             ( const std::string& appName );
        void add                ( string const &appName );
        void add                ( string const &appName, attributes const &attrs );

        attributes const & operator []   ( string const &appName )const;		
        attributes       & operator []   ( string const &appName )const;		

        typedef IniData::iterator       iterator;
        typedef IniData::const_iterator const_iterator;

        const_iterator  begin   () const;
        const_iterator  end     () const;
        iterator        begin   ();
        iterator        end     ();

    private:
		
        IniData data;
	};

}

#endif
