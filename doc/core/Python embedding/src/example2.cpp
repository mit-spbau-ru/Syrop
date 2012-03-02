#include <string>
#include <boost/python.hpp>

class A {
	private:
		std::string m_greeting;
	public:
		A(const std::string &greeting) : m_greeting(greeting)
			{}

		std::string write()
		{
			return "Hello world";
		}
};

namespace bp = boost::python;

int main()
{
	Py_Initialize();
	try
	{
		A a("Hello world");
		bp::object main_module = bp::import("__main__");
		bp::object main_namespace = main_module.attr("__dict__");
		main_namespace["A"] = bp::class_<A>("A", bp::no_init)
					.def("write", &A::write);
		main_namespace["a"] = bp::ptr(&a);
		bp::object ignored = bp::exec_file("script.py",
						main_namespace);
	}
	catch (bp::error_already_set const&)
	{
		PyErr_Print();
	}
	Py_Finalize();

	return EXIT_SUCCESS;
}
