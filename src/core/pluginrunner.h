#ifndef _CORE_PLUGINRUNNER_
#define _CORE_PLUGINRUNNER_

#include <string>
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>

#include "system.h"
#include "appsettings.h"

namespace bpy = boost::python;

namespace core
{

	/**
	 * Class initialize Python interpreter and call plugins specified by script name
	 */
	class PluginRunner : public boost::noncopyable
	{
	public:
		/**
		 * Constructor inititalize Python interpreter and prepare main module
		 */
		PluginRunner()
		{
			Py_Initialize();
			myMain = bpy::import("__main__").attr("__dict__");
			myMain["AppSettings"] = bpy::class_<utils::AppSettings>("AppSettings", bpy::no_init)
								.def("getProxy", &utils::AppSettings::getAttribute)
								.def("hasProxy", &utils::AppSettings::hasAttribute);
		}
		
		/**
		 * Method calls setupSettings function with settings in the Python script
		 *
		 * @param script Python script name
		 * @param settings AppProxySettings
		 * @throws error_already_set if an Python interpreter error occurred
		 */
		void setupSettings(std::string const &script, utils::AppSettings const &settings);
		
		/**
		 * Method calls celanupSettings function in the Python script
		 *
		 * @param script Python script name
		 * @throws error_already_set if an Python intepreter error occurred
		 */
		void cleanupSettings(std::string const &script);
		
		/**
		 * Destructor finalize Python interpreter
		 */
		~PluginRunner()
		{
			Py_Finalize();
		}

	private:
		bpy::object myMain;
	};
} // namespace core
#endif //_CORE_PLUGINRUNNER_