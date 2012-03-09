#ifndef _CORE_H_
#define _CORE_H_

#include <string>
#include <map>
#include <vector>

#include "../includes/system.h"

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
	std::vector<std::string> getSearchPath() throw(utils::SystemException);
	
	/**
	 * Return map of plugins in a diretories specified in the path argument
	 *
	 * #param path vectror of search pathes
	 * @return set of pairs (plugin name, main plugin file)
	 * @throws SystemException if an system error occurred
	 */
	std::map<std::string, std::string> listPlugins(std::vector<std::string> path) throw(utils::SystemException);

} // namespace core

#endif //_CORE_H_