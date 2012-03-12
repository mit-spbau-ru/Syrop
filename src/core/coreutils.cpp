#include "coreutils.h"

namespace core
{

static bool testPlugin(utils::FileInfo const &info) throw(utils::SystemException)
{
	//plugin is a direcotiry with a python script
	if (info.isDirectory())
	{
		//list files
		std::vector<utils::FileInfo> children = utils::listDirEntries(info.getFullName());
		for (std::vector<utils::FileInfo>::iterator it = children.begin(); it != children.end(); ++it)
			if (it->getName() == (info.getName() + ".py") )
				//main plugin file must have same name as plugin directory
				return true;
	}
	return false;
}

//function adds plugins in a specified directory to map
static void listPlugins(std::string const &dir, std::map<std::string, std::string> &plugins) throw(utils::SystemException)
{
	std::vector<utils::FileInfo> children = utils::listDirEntries(dir);
	for (std::vector<utils::FileInfo>::iterator it = children.begin(); it != children.end(); ++it)
		if (testPlugin(*it))
			plugins.insert(std::pair<std::string, std::string>( it->getName(), it->getFullName() ) );
}

std::vector<std::string> getSearchPath() throw(utils::SystemException)
{
	std::vector<std::string> path;
	path.push_back(utils::getUserHomeDir() + "/.syrop/plugins");
	path.push_back("/usr/share/syrop/plugins");
	return path;
}

std::map<std::string, std::string> listPlugins(std::vector<std::string> path) throw(utils::SystemException)
{
	std::map<std::string, std::string> plugins;
	//for every path in a vector
	for (std::vector<std::string>::iterator it = path.begin(); it != path.end(); ++it)
		listPlugins(*it, plugins);
	return plugins;
}

} // namespace core