DEFINES += $$upper($$basename(PWD))_USED

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/couchdbdocument.cpp \
    $$PWD/couchdbdatabase.cpp \
    $$PWD/couchdbview.cpp \
    $$PWD/couchdbmodel.cpp

HEADERS += \
    $$PWD/couchdbdocument.h \
    $$PWD/couchdbdatabase.h \
    $$PWD/couchdbview.h \
    $$PWD/couchdbmodel.h

RESOURCES +=

OTHER_FILES +=
