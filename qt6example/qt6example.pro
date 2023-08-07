greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TEMPLATE     = app
TARGET       = qt6example
QT          += core gui widgets
INCLUDEPATH += ./inc ../../tools/include

DESTDIR      = bin
OBJECTS_DIR  = ./obj
MOC_DIR      = ./obj
UI_DIR       = ./obj
RCC_DIR      = ./obj

QMAKE_CXXFLAGS += -Wno-deprecated-declarations

LIBS += -L../../tools/lib -ljsoncpp

SOURCES += src/actions.cpp \
           src/controls.cpp \
           src/darkstyle.cpp \
           src/docks.cpp \
           src/framelesswindow.cpp \
           src/main.cpp\
           src/menus.cpp \
           src/preferences.cpp \
           src/releasenotes.cpp \
           src/settings.cpp \
           src/slots.cpp \
           src/toolbars.cpp \
           src/windowdragger.cpp \
           src/xmw.cpp


HEADERS += inc/app.h \
           inc/controls.h \
           inc/darkstyle.h \
           inc/docks.h \
           inc/framelesswindow.h \
           inc/preferences.h \
           inc/windowdragger.h \
           inc/xmw.h

FORMS += forms/framelesswindow.ui
RESOURCES += qrc/darkstyle.qrc \
             qrc/framelesswindow.qrc
