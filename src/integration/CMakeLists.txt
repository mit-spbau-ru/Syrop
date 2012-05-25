project(syrop-daemon CXX)

find_package(PkgConfig)
pkg_check_modules(DBUS_GLIB dbus-glib-1)

set(SYROP_LIBRARY_DIRS ../../../build/ars)
set(SYROP_INCLUDE_PATH ../../includes)
set(SYROP_LIBRARIES syroputils)

link_directories(
	${DBUS_GLIB_LIBRARY_DIRS}
	${SYROP_LIBRARY_DIRS}
)

include_directories(
	${DBUS_GLIB_INCLUDE_DIRS}
	${SYROP_INCLUDE_PATH}
)

add_executable(syropd
               main.cpp
               daemonexception.cpp
               CExecuter.cpp
               CBusMessage.cpp
)

target_link_libraries(syropd
	${SYROP_LIBRARIES}
	${DBUS_GLIB_LIBRARIES}
)

install(TARGETS syropd DESTINATION bin)
