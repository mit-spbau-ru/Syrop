#ifndef _CORE_COREUTILS_H_
#define _CORE_COREUTILS_H_

#include <string>
#include <map>
#include <vector>

namespace core
{
	/**
	 * Function returns standart plugin search path:
	 *	$HOME/.syrop/plugins
	 *	/usr/share/syrop/plugins
	 *
	 * @return vector of a string with path
	 * @throws SystemException if an system error occurred
	 */
	std::vector<std::string> const &getSearchPathes(); // throws SystemException
	
	/**
	 * Return map of plugins in a diretories specified in the path argument
	 *
	 * @param path vectror of search pathes
	 * @param plugins set of pairs (plugin name, main plugin file)
	 * @throws SystemException if an system error occurred
	 */
	void listPlugins(std::vector<std::string> const &path, std::map<std::string, std::string> &plugins); // throws SystemException

} // namespace core

#endif //_CORE_COREUTILS_H_