project(syrop CXX)

cmake_minimum_required(VERSION 2.6)

find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonLibs REQUIRED)

set(SYROP_BIN ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SYROP_BIN}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SYROP_BIN}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SYROP_BIN}/ars)

set(SYROP_INCLUDE_PATH src/includes)
include_directories(${SYROP_INCLUDE_PATH})

set(CMAKE_INSTALL_PREFIX /usr)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Syrop auto proxy configurating tools")
set(CPACK_PACKAGE_VERSION 1.0.0)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "krinkin.m.u@gmail.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-python${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libc6 (>= 2.3.6-6~), libc6 (>= 2.4), libgcc1 (>= 1:4.1.1), libpython2.7 (>= 2.7), libstdc++6 (>= 4.1.1)")

set(CPACK_BINARY_DEB ON)
set(CPACK_BINARY_RPM OFF)
set(CPACK_BINARY_STGZ OFF)
set(CPACK_BINARY_TGZ OFF)
set(CPACK_BINARY_TZ OFF)
set(CPACK_BINARY_TBZ2 OFF)

add_subdirectory(src)

include(CPack)
