#include "pluginrunner.h"

namespace core
{

void PluginRunner::setupSettings(std::string const &script, core::AppProxySettings const &settings) throw(bp::error_already_set)
{
	//load script
	bp::object ignored = bp::exec_file(bp::str(script), myMain);
	//find setupSettings function by name
	bp::object setup = myMain["setupSettings"];
	//call
	setup(bp::ptr(&settings));
}

void PluginRunner::cleanupSettings(std::string const &script) throw(bp::error_already_set)
{
	bp::object ignored = bp::exec_file(bp::str(script), myMain);
	bp::object cleanup = myMain["cleanupSettings"];
	cleanup();
}

} // namespace core