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
    enginebase.cpp \
    engineinterface.cpp \
    itemsfactory.cpp \
    messageanswerdispatcher.cpp \
    messageheader.cpp \
    messagenegotiator.cpp

HEADERS += \
    abstractobjectcontroller.h \
    basemovecontroller.h \
    circlebuffer.h \
    core_global.h \
    emptymessage.h \
    enginebase.h \
    engineinterface.h \
    imessage.h \
    itemsfactory.h \
    messageanswerdispatcher.h \
    messageheader.h \
    messagenegotiator.h

