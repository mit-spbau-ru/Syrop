#ifndef _PLUGIN_RUNNER_
#define _PLUGIN_RUNNER_

#include <string>
#include <boost/python.hpp>

#include "../includes/system.h"

//dummy AppProxySettings
#include "appsettings.h"

namespace bp = boost::python;

namespace core
{

	/**
	 * Class initialize Python interpreter and call plugins specified by script name
	 */
	class PluginRunner
	{
		public:
			/**
			 * Constructor inititalize Python interpreter and prepare main module
			 */
			PluginRunner()
			{
				Py_Initialize();
				myMain = bp::import("__main__").attr("__dict__");
				myMain["AppProxySettings"] = bp::class_<AppProxySettings>("AppProxySettings", bp::no_init)
									.def("getProxy", &AppProxySettings::getProxy);
			}
			
			/**
			 * Method calls setupSettings function with settings in the Python script
			 *
			 * @param script Python script name
			 * @param settings AppProxySettings
			 * @throws error_already_set if an Python interpreter error occurred
			 */
			void setupSettings(std::string const &script, core::AppProxySettings const &settings) throw(bp::error_already_set);
			
			/**
			 * Method calls celanupSettings function in the Python script
			 *
			 * @param script Python script name
			 * @throws error_already_set if an Python intepreter error occurred
			 */
			void cleanupSettings(std::string const &script) throw(bp::error_already_set);
			
			/**
			 * Destructor finalize Python interpreter
			 */
			~PluginRunner()
			{
				Py_Finalize();
			}
	
		private:
			bp::object myMain;
			
			//I don't know whether it safe, anyway it is no needed
			PluginRunner(PluginRunner const &);
			PluginRunner& operator=(PluginRunner const &);
	};

} // namespace core
#endif //_PLUGIN_RUNNER_