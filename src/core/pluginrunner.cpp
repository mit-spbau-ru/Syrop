#include "pluginrunner.h"

namespace core
{

void PluginRunner::setupSettings(std::string const &script, utils::AppSettings const &settings)
{
	try
	{
		//load script
		bpy::object const ignored = bpy::exec_file(bpy::str(script), myMain);
		//find setupSettings function by name
		bpy::object const setup = myMain["setupSettings"];
		//call
		setup(bpy::ptr(&settings));
	}
	catch (bpy::error_already_set const& e)
	{
		PyErr_Print();
	}
}

void PluginRunner::cleanupSettings(std::string const &script)
{
	try
	{
		bpy::object const ignored = bpy::exec_file(bpy::str(script), myMain);
		bpy::object const cleanup = myMain["cleanupSettings"];
		cleanup();
	}
	catch (bpy::error_already_set const& e)
	{
		PyErr_Print();
	}
}

} // namespace core
