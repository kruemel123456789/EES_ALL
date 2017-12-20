#additional Qt modules
QT -= gui
QT += websockets network

#Include project files
INCLUDEPATH += $$PWD

SOURCES += main.cpp \
    chatServer.cpp

HEADERS += \
    chatServer.h

RESOURCES += 

OTHER_FILES +=

#use c++11 compiler flags
CONFIG += c++11 

