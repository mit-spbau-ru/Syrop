#ifndef _INCLUDES_EMPTYOBJECTEXCEPTION
#define _INCLUDES_EMPTYOBJECTEXCEPTION

class EmptyObjectException
{

	public:

	EmptyObjectException() {}
	~EmptyObjectException() {}
	char const * showReason() const 
	{ 
		return "try to access unexistent object"; 
	}

};

#endif
