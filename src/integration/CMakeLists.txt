project(syrop-daemon CXX)

EXEC_PROGRAM(pkg-config ARGS --cflags dbus-glib-1 OUTPUT_VARIABLE DbusGlib_FLAGS)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DbusGlib_FLAGS}")

EXEC_PROGRAM(pkg-config ARGS --libs dbus-glib-1 OUTPUT_VARIABLE DbusGlib_LIBS)


add_executable(syropd
	       syropd.cpp
)

target_link_libraries(syropd
	syroputils
	${DbusGlib_LIBS}
)

install(TARGETS syropd DESTINATION bin)
