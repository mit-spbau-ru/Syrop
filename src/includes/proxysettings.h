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
#include "appsettings.h"
#include "iniparser.h"

namespace utils{

	class ProxySettings
	{
	
	public:

		void loadData( string const &fileName );

		AppSettings getAppSettings( string const &sec ) const;
		vector< AppSettings > getAllSettings () const;

		void save ( AppSettings const & apps ) ;
		void save ( vector < AppSettings > const & apps ) ;
		AppSettings addNewApp( string const &name ) ;

		//void print() const;
		friend std::ostream& operator<<( std::ostream &os, ProxySettings const & ps );

	private:
		void saveIniData ( AppSettings const & apps ) ;
		void fix( IniData const &idata ) const;	

		IniData data;
		string fileName;	
	};

}

#endif
