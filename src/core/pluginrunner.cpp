#include "pluginrunner.h"

namespace core
{

void PluginRunner::setupSettings(std::string const &script, core::AppProxySettings const &settings)
{
	//load script
	bpy::object ignored = bpy::exec_file(bpy::str(script), myMain);
	//find setupSettings function by name
	bpy::object setup = myMain["setupSettings"];
	//call
	setup(bpy::ptr(&settings));
}

void PluginRunner::cleanupSettings(std::string const &script)
{
	bpy::object ignored = bpy::exec_file(bpy::str(script), myMain);
	bpy::object cleanup = myMain["cleanupSettings"];
	cleanup();
}

} // namespace core