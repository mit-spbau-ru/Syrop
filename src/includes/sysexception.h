#ifndef _UINCLUDES_SYSEXCEPTION_H_
#define _UINCLUDES_SYSEXCEPTION_H_

#include <string>
#include <exception>

namespace utils {

	/**
	 * SystemException throws by system utilitites if an error occured
	 *
	 * @see system.cpp
	 */
	class SystemException : public std::exception
	{
	public:
		/**
		 * Class constructor
		 *
		 * @param msg error message
		 */
		SystemException(std::string msg)
		: std::exception()
		, myMessage(msg)
		{}
		
		~SystemException() throw()
		{}
		
		const char* what() const throw()
		{
			return myMessage.c_str();
		}
		
	private:
		std::string myMessage;
	};
	
} //namespace utils

#endif //_INCLUDES_SYSEXCEPTION_H_