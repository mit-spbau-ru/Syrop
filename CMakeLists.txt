project(syrop-full CXX)

set(SYROP_BIN ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SYROP_BIN}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SYROP_BIN}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SYROP_BIN}/ars)

set(SYROP_INCLUDE_PATH src/includes)
include_directories(${SYROP_INCLUDE_PATH})

add_subdirectory(src)