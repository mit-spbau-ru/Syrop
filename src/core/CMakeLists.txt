project(syrop-core CXX)

add_executable(syrop
		coreutils.cpp
		pluginrunner.cpp
		main.cpp
)

find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(
	${Boost_INCLUDE_DIRS}
	${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(syrop
	syroputils
	${Boost_LIBRARIES}
	${PYTHON_LIBRARIES}
)

install(TARGETS syrop DESTINATION bin)