#include <boost/python.hpp>

int main()
{
	namespace bp = boost::python;
	try
	{
		Py_Initialize();
		bp::object main_module = bp::import("__main__");
		bp::object main_namespace = main_module.attr("__dict__");
		bp::object ignored = bp::exec("hello = file('hello.txt', 'w')\n"
						"hello.write('Hello world!')\n"
						"hello.close()",
						main_namespace);
		Py_Finalize();
	}
	catch (bp::error_already_set const&)
	{
		PyErr_Print();
	}

	return EXIT_SUCCESS;
}
