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

#ifndef _INCLUDES_INIDATA_
#define _INCLUDES_INIDATA_

#include <iostream>
#include <string>
#include <vector>
#include <map>


namespace utils
{
                           
	using std::string;
	using std::map;
	using std::pair;
	using std::vector;

	typedef map <string, string> attributes;
	typedef	map <string, attributes> attributes_map;

	class IniData{

	public:

        void addSection                     ( string const &sec );
		
        void addAttribute                   ( string const &sec, pair <string, string> const &params );
        void removeSection                  ( string const &sec );
        void removeAttribute                ( string const &attr );

        void dropAll                        () { data.clear(); }
		
        attributes         getSection       ( string const &sec ) const;
        attributes       & operator[]       ( string const &appName );
        attributes const & operator[]       ( string const &appName ) const;

        bool hasSection                     ( string const &sec ) const;
        bool hasAttribute                   ( string const &sec, string const &attr ) const;
        vector< string > getSectionsList    () const;
        string getAttribute                 ( string const &sec, string const &param_first ) const;

        typedef attributes_map::const_iterator const_iterator;

        typedef attributes_map::iterator iterator; 

        const_iterator begin 	() const;
        const_iterator end 	    () const;
       
        iterator begin 	    ();
        iterator end 		();
            
    private:
        attributes_map data;
		
    };
}

#endif
