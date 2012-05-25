project(syrop-gui-gtk CXX)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

set(SYROP_LIBRARY_DIRS ../../../build/ars)
set(SYROP_INCLUDE_PATH ../../includes)
set(SYROP_LIBRARIES syroputils)
#set(CMAKE_CXX_FLAGS "-g3")

link_directories(
	${GTKMM_LIBRARY_DIRS}
	${SYROP_LIBRARY_DIRS}
)

include_directories(
	${GTKMM_INCLUDE_DIRS}
	${SYROP_INCLUDE_PATH}
)

add_executable(syrop-gtk
	       main.cpp
	       mainwindow.cpp
	       networkslist.cpp
	       networkview.cpp
	       mappingdialog.cpp
	       inputdialog.cpp
	       yesnodialog.cpp
	       selectdialog.cpp
	       applicationview.cpp
	       authwidget.cpp
	       proxywidget.cpp
	       textwidget.cpp
)

target_link_libraries(syrop-gtk
		${SYROP_LIBRARIES}
		${GTKMM_LIBRARIES}
)

install(TARGETS syrop-gtk DESTINATION bin)

set(CMAKE_INSTALL_PREFIX /usr)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Syrop GTK+ user interface")
set(CPACK_PACKAGE_VERSION 1.0.0)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "krinkin.m.u@gmail.com")

set(CPACK_BINARY_DEB ON)
set(CPACK_BINARY_RPM OFF)
set(CPACK_BINARY_STGZ OFF)
set(CPACK_BINARY_TGZ OFF)
set(CPACK_BINARY_TZ OFF)
set(CPACK_BINARY_TBZ2 OFF)

include(CPack)
