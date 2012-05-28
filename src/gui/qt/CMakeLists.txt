project( SyropGui )

cmake_minimum_required(VERSION 2.8.1)
cmake_policy(SET CMP0015 NEW)

set(CMAKE_BUILD_TYPE Release )
set(SYROP_LIBRARIES syroputils)
set(SYROP_LIBRARY_DIRS ../../../build/ars)
set(SYROP_LIBRARIES syroputils)
set(SYROP_EXECUTABLE syrop-qt)

link_directories(
    ${SYROP_LIBRARY_DIRS}
)

add_definitions ( -Wall )
find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	../../includes)
set ( SyropGui_HDRS)

set ( SyropGui_SRCS
	main.cpp
	mainwindow.cpp
	dialogaddnetwork.cpp
	applicationsettingstab.cpp
	dialogabout.cpp
	datamodel.cpp
	dialogaddapp.cpp
    dialogeditnetwork.cpp
    formfieldauth.cpp
    formfieldproxy.cpp
    formfieldtext.cpp
	)

set ( SyropGui_UIS
	mainwindow.ui
	dialogaddnetwork.ui
	applicationsettingstab.ui
	dialogabout.ui
	dialogaddapp.ui
    dialogeditnetwork.ui
    formfieldauth.ui
    formfieldproxy.ui
    formfieldtext.ui
	)
QT4_WRAP_UI(UIS ${SyropGui_UIS})

set ( SyropGui_MOCS
	mainwindow.h
	dialogaddnetwork.h
	applicationsettingstab.h
	datamodel.h
	dialogabout.h
	dialogaddapp.h
    dialogeditnetwork.h
    formfieldauth.h
    formfieldproxy.h
    formfieldtext.h
    formpluginfield.h
	)
QT4_WRAP_CPP(MOCS ${SyropGui_MOCS})

add_executable ( ${SYROP_EXECUTABLE} ${SyropGui_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )

target_link_libraries ( ${SYROP_EXECUTABLE} 
    ${QT_QTCORE_LIBRARY} 
    ${QT_QTGUI_LIBRARY} 
	${SYROP_LIBRARIES}
)

