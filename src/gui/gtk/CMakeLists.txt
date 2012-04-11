project(syrop-gui-gtk CXX)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4)
pkg_check_modules(GLADE libglademm-2.4)

link_directories(
	${GTKMM_LIBRARY_DIRS}
	${GLADE_LIBRARY_DIRS}
)

set(SYROP_INCLUDE_PATH ../../src/includes)
include_directories(
	${SYROP_INCLUDE_PATH}
	${GTKMM_INCLUDE_DIRS}
	${GLADE_INCLUDE_DIRS}
)

add_executable(syrop-gtk
	       main.cpp
)

target_link_libraries(syrop-gtk
		${GTKMM_LIBRARIES}
		${GLADE_LIBRARIES}
)

add_subdirectory(rc)

install(TARGETS syrop-gtk DESTINATION bin)

set(SYROP_BIN ${CMAKE_SOURCE_DIR}/../../build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SYROP_BIN}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SYROP_BIN}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SYROP_BIN}/ars)

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
