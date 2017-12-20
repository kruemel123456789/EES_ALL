QT += core websockets
QT       -= gui
CONFIG += c++11
CONFIG   += console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$modules_dir/couchdb/couchdb.pri)
include($$modules_dir/qjsonrpc/qjsonrpc.pri)
include($$modules_dir/qdiscoveryservice/qdiscoveryservice.pri)

SOURCES += main.cpp \
    AppControlModules/orderqueueconnector.cpp \
    AppControlModules/utils.cpp \
    Tests/orderqueuetests.cpp \
    Tests/clienttests.cpp \
    AppControlModules/logic.cpp \
    AppControlModules/rpc/server.cpp \
    AppControlModules/rpc/client.cpp \
    libs/leds.cpp \
    libs/dma.c \
    libs/mailbox.c \
    libs/own_lib.c \
    libs/pcm.c \
    libs/pwm.c \
    libs/rpihw.c \
    libs/ws2811.c



# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AppControlModules/orderqueueconnector.h \
    AppControlModules/utils.h \
    Tests/orderqueuetests.h \
    Tests/clienttests.h \
    AppControlModules/logic.h \
    AppControlModules/rpc/server.h \
    AppControlModules/rpc/client.h \
    libs/clk.h \
    libs/dma.h \
    libs/gpio.h \
    libs/leds.h \
    libs/mailbox.h \
    libs/own_lib.h \
    libs/pcm.h \
    libs/pwm.h \
    libs/rpihw.h \
    libs/version.h \
    libs/ws2811.h

CONFIG += qmltestcase
QT += testlib

#TEMPLATE = subdirs

#SUBDIRS += ../AppControlTest

