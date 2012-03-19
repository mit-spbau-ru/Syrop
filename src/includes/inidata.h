#ifndef _INCLUDES_INIDATA_
#define _INCLUDES_INIDATA_

#include <iostream>
#include <string>
#include <vector>
#include <map>


namespace utils{

	using std::string;
	using std::map;
	using std::pair;
	using std::vector;

	typedef map <string, string> attributes;

	class IniData{

	public:
		void addSection( string const &sec );
		//void addSection(string const &, string const &);
		void addAttribute( string const &sec, pair <string, string> const &params );
		void removeSection( string const &sec );
		void removeAttribute( string const &attr );
		
		attributes getSection( string const &sec ) const;
		bool hasSection( string const &sec ) const;
		bool hasAttribute( string const &sec, string const &attr ) const;
		vector< string > getSectionsList() const;
		string getAttribute( string const &sec, string const &param_first ) const;

		//void print() const ;

		friend std::ostream& operator<<( std::ostream &os, IniData const & idata );

	private:
		map <string, attributes> data;
		
	};
}

#endif
