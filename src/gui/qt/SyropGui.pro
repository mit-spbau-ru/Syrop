#-------------------------------------------------
#
# Project created by QtCreator 2012-03-05T14:44:59
#
#-------------------------------------------------

QT       += core gui

TARGET = SyropGui
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    dialogaddnetwork.cpp \
    applicationsettingstab.cpp \
    dialogabout.cpp \
    datamodel.cpp \
    dialogaddapp.cpp \
    dialogeditnetwork.cpp \
    formfieldproxy.cpp \
    formfieldauth.cpp \
    formfieldtext.cpp

HEADERS  += \
    mainwindow.h \
    dialogaddnetwork.h \
    applicationsettingstab.h \
    datamodel.h \
    dialogabout.h \
    dialogaddapp.h \
    dialogeditnetwork.h \
    formfieldproxy.h \
    formpluginfield.h \
    formfieldauth.h \
    formfieldtext.h

FORMS    += \
    mainwindow.ui \
    dialogaddnetwork.ui \
    applicationsettingstab.ui \
    dialogabout.ui \
    dialogaddapp.ui \
    dialogeditnetwork.ui \
    formfieldproxy.ui \
    formfieldauth.ui \
    formfieldtext.ui

INCLUDEPATH += $$PWD/../../includes
DEPENDPATH += $$PWD/../../includes

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../utils/release/ -lsyroputils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../utils/debug/ -lsyroputils
else:symbian: LIBS += -lsyroputils
else:unix: LIBS += -L$$PWD/../../utils/ -lsyroputils

INCLUDEPATH += $$PWD/../../includes
DEPENDPATH += $$PWD/../../includes

OTHER_FILES += \
    tasks.txt \
    tasksHistory.txt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build/ars/release/ -lsyroputils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/ars/debug/ -lsyroputils
else:symbian: LIBS += -lsyroputils
else:unix: LIBS += -L$$PWD/../../../build/ars/ -lsyroputils

INCLUDEPATH += $$PWD/../../includes
DEPENDPATH += $$PWD/../../includes

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../build/ars/release/syroputils.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../build/ars/debug/syroputils.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../build/ars/libsyroputils.a
