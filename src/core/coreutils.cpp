#include "system.h"
#include "coreutils.h"
#include "sysexception.h"

using utils::FileInfo;
using utils::listDirEntries;
using utils::getUserHomeDir;

using std::vector;
using std::map;
using std::string;
using std::make_pair;

namespace core
{

static bool testPlugin(FileInfo const &info)
{
	//plugin is a direcotiry with a python script
	if (info.isDirectory())
	{
		//list files
		vector<FileInfo> children = listDirEntries(info.getFullName());
		for (vector<FileInfo>::const_iterator it = children.begin(); it != children.end(); ++it)
			if (it->getName() == (info.getName() + ".py") )
				//main plugin file must have same name as plugin directory
				return true;
	}
	return false;
}

//function adds plugins in a specified directory to map
static void listPlugins(string const &dir, map<string, string> &plugins)
{
	vector<FileInfo> children = listDirEntries(dir);
	for (vector<FileInfo>::const_iterator it = children.begin(); it != children.end(); ++it)
		if (testPlugin(*it))
			plugins.insert(make_pair<string, string>( it->getName(), it->getFullName() ) );
}

vector<string> const& getSearchPathes()
{
	static vector<string> pathes;
	if (pathes.empty())
	{
		try
		{
			string name = getUserHomeDir() + "/.syrop/plugins";
			FileInfo info(name);
			pathes.push_back(name);
		}
		catch (utils::SystemException const &e)
		{}
		
		try
		{
			FileInfo info("/usr/share/syrop/plugins");
			pathes.push_back("/usr/share/syrop/plugins");
		}
		catch (utils::SystemException const &e)
		{}
	}
	return pathes;
}

void listPlugins(vector<string> const& pathes, map<string, string> &plugins)
{
	//for every path in a vector
	for (vector<string>::const_iterator it = pathes.begin(); it != pathes.end(); ++it)
		listPlugins(*it, plugins);
}

} // namespace core