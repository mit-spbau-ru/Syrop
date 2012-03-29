#ifndef _INCLUDES_EMPTYOBJECTEXCEPTION
#define _INCLUDES_EMPTYOBJECTEXCEPTION
#include <exception>

class EmptyObjectException : public std::exception
{

	public:

	EmptyObjectException() {}

	char const * showReason() const 
	{ 
		return "try to access unexistent object"; 
	}

};

#endif
