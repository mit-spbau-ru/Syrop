#ifndef _INCLUDES_FILELOCKS_H_
#define _INCLUDES_FILELOCKS_H_

namespace utils
{

	bool locked(std::string const& where, std::string const& what);
	bool lock(std::string const& where, std::string const& what);
	bool unlock(std::string const& where, std::string const& what);

} // namespace utils

#endif // _INCLUDES_FILELOCKS_H_ 
