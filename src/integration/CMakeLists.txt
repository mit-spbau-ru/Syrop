project(syrop-daemon CXX)

find_package(PkgConfig)
pkg_check_modules(GLIB, glib-2.0)
pkg_check_modules(DBUS, dbus-glib-1)

#set(GLIB_INCLUDE_PATH `pkg-config --cflags glib-2.0`)
set(GLIB_INCLUDE_PATH -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include)
#set(DBUS-GLIB_INCLUDE_PATH `pkg-config --cflags dbus-glib-1`)
set(DBUS-GLIB_INCLUDE_PATH -pthread -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include)
#set(GLIBP_LIBRARYS `pkg-config --libs glib-2.0`)
set(GLIBP_LIBRARYS -lglib-2.0)
#set(DBUS-GLIB_LIBRARYS `pkg-config --libs dbus-glib-1`)
set(DBUS-GLIB_LIBRARYS -pthread -ldbus-glib-1 -ldbus-1 -lpthread -lgobject-2.0 -lgthread-2.0 -lrt -lglib-2.0)

add_executable(syropd
	       syropd.cpp
)

include_directories(
	${GLIB_INCLUDE_PATH}
	${DBUS-GLIB_INCLUDE_PATH}
)

target_link_libraries(syrop
	syroputils
	${GLIBP_LIBRARYS}
	${DBUS-GLIB_LIBRARYS}
)

install(TARGETS syropd DESTINATION bin)
