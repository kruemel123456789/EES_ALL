DEFINES += $$upper($$basename(PWD))_USED

QT += websockets

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qjsonrpcserver.cpp \
    $$PWD/qjsonrpcclient.cpp


HEADERS += \
    $$PWD/qjsonrpcserver.h \
    $$PWD/qjsonrpcclient.h

