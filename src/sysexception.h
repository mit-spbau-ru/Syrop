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
	class SystemException : public std::runtime_error
	{
	public:
		/**
		 * Class constructor
		 *
		 * @param msg error message
		 */
		SystemException(std::string msg)
		: std::runtime_error(msg)
		{}
	};
	
} //namespace utils

#endif //_INCLUDES_SYSEXCEPTION_H_