#ifndef _SYSTEM_EXCEPTION_H_
#define _SYSTEM_EXCEPTION_H_

#include <string>

namespace utils {

	/**
	 * SystemException throws by system utilitites if an error occured
	 *
	 * @see system.cpp
	 */
	class SystemException
	{
		public:
			/**
			 * Class constructor
			 *
			 * @param msg error message
			 */
			SystemException(std::string msg)
			: myMessage(msg)
			{}
		
			/**
			 * Method returns error message
			 *
			 * @return error message
			 */
			std::string getMessage() const { return myMessage; }
		
		private:
			const std::string myMessage;
	};
	
} //namespace utils

#endif //_SYSTEM_EXCEPTION_H_