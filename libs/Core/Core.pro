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
    emptymessage.cpp \
    engine.cpp \
    engineinterface.cpp \
    imesssage.cpp \
    itemsfactory.cpp \
    messageanswerdispatcher.cpp \
    messagebase.cpp \
    messageheader.cpp \
    messagenegotiator.cpp

HEADERS += \
    abstractobjectcontroller.h \
    basemovecontroller.h \
    circlebuffer.h \
    core_global.h \
    emptymessage.h \
    engine.h \
    engineinterface.h \
    imesssage.h \
    itemsfactory.h \
    messageanswerdispatcher.h \
    messagebase.h \
    messageheader.h \
    messagenegotiator.h

