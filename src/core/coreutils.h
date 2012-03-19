#ifndef _CORE_COREUTILS_H_
#define _CORE_COREUTILS_H_

#include <string>
#include <map>
#include <vector>

namespace core
{
	const std::string home = ".syrop/";
	const std::string plugins = "plugins/";
	const std::string configs = "configs/";
	const std::string setup = "/usr/share/syrop/";
	const std::string pluginExtention = ".py";

	/**
	 * Function returns application HOME dir. Directory will be
	 * created if doesn't exist;
	 *
	 * @return string with directory name
	 * @throws std::runtime_error if an error occrred
	 */
	std::string getApplicationDir();

	/**
	 * Function returns standart plugin search path:
	 *	$HOME/.syrop/plugins
	 *	/usr/share/syrop/plugins
	 *
	 * @return vector of a string with path
	 * @throws std::runtime_error if an system error occurred
	 */
	std::vector<std::string> const &getSearchPathes(); // throws std::runtime_error
	
	/**
	 * Return map of plugins in a diretories specified in the path argument
	 *
	 * @param path vectror of search pathes
	 * @param plugins set of pairs (plugin name, main plugin file)
	 * @throws std::runtime_error if an system error occurred
	 */
	void listPlugins(std::vector<std::string> const &path, std::map<std::string, std::string> &plugins); // throws std::runtime_error

} // namespace core

#endif //_CORE_COREUTILS_H_