QT -= gui
QT += concurrent
QT += core
TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++17

SOURCES += \
    abstractobjectcontroller.cpp \
    basemovecontroller.cpp \
    circlebuffer.cpp \
    createitemmessage.cpp \
    emptymessage.cpp \
    enginebase.cpp \
    engineinterface.cpp \
    itemsfactory.cpp \
    levelgenerator.cpp \
    messageanswerdispatcher.cpp \
    messageheader.cpp \
    messagenegotiator.cpp \
    removeitemmessage.cpp \
    setmodeenginemsg.cpp

HEADERS += \
    abstractobjectcontroller.h \
    basemovecontroller.h \
    circlebuffer.h \
    core_global.h \
    createitemmessage.h \
    emptymessage.h \
    enginebase.h \
    engineinterface.h \
    imessage.h \
    itemsfactory.h \
    levelgenerator.h \
    messageanswerdispatcher.h \
    messageheader.h \
    messagenegotiator.h \
    removeitemmessage.h \
    setmodeenginemsg.h

