#c++11 support
CONFIG += c++11 

#base settings
QT       += gui widgets charts
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

#make the executable search for .so-files in the same folder under linux
QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"

SOURCES += \
    Application.cpp \
    GUIHelper.cpp \
    FileChooser.cpp \
    ClickableLabel.cpp \
    ClickableLineEdit.cpp \
    ColorSelector.cpp \
    ScrollableTextDialog.cpp \
    BusyDialog.cpp \
    QrCodeGenerator/BitBuffer.cpp \
    QrCodeGenerator/QrCode.cpp \
    QrCodeGenerator/QrSegment.cpp \
    QrCodeFactory.cpp \
    DelayedInitializationTimer.cpp \
    TsvTableWidget.cpp \
    ImageLabel.cpp

HEADERS += \
    Application.h \
    GUIHelper.h \
    FileChooser.h \
    ClickableLabel.h \
    ClickableLineEdit.h \
    ColorSelector.h \
    ScrollableTextDialog.h \
    BusyDialog.h \
    QrCodeGenerator/BitBuffer.h \
    QrCodeGenerator/QrCode.h \
    QrCodeGenerator/QrSegment.h \
    QrCodeFactory.h \
    DelayedInitializationTimer.h \
    TsvTableWidget.h \
    ImageLabel.h
    
RESOURCES += \
    resources.qrc

FORMS += \
    ScrollableTextDialog.ui \
    BusyDialog.ui \
    TsvTableWidget.ui
