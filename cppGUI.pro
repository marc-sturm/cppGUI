#c++11 and c++14 support
CONFIG += c++14

#base settings
QT       += gui widgets
TEMPLATE = lib
TARGET = cppGUI
DEFINES += CPPGUI_LIBRARY

#enable O3 optimization
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

#copy DLL to bin folder
DESTDIR = ../../bin/

#include cppCORE library
INCLUDEPATH += $$PWD/../cppCORE
LIBS += -L$$PWD/../../bin -lcppCORE

SOURCES += \
    Application.cpp \
    GUIHelper.cpp \
    FileChooser.cpp \
    ClickableLabel.cpp \
    ColorSelector.cpp \
    ScrollableTextDialog.cpp \
    BusyDialog.cpp

HEADERS += \
    Application.h \
    GUIHelper.h \
    FileChooser.h \
    ClickableLabel.h \
    ColorSelector.h \
    ScrollableTextDialog.h \
    BusyDialog.h
    
RESOURCES += \
    resources.qrc

FORMS += \
    ScrollableTextDialog.ui \
    BusyDialog.ui
