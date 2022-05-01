QT -= gui
QT += concurrent
QT += core
TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++20

SOURCES += \
    abstractobjectcontroller.cpp \
    circlebuffer.cpp \
    collisiondetector.cpp \
    emptymessage.cpp \
    enginebase.cpp \
    engineinterface.cpp \
    levelgenerator.cpp \
    levelobjectcreator.cpp \
    messageanswerdispatcher.cpp \
    messageheader.cpp \
    messagenegotiator.cpp

HEADERS += \
    abstractobjectcontroller.h \
    circlebuffer.h \
    collisiondetector.h \
    core_global.h \
    emptymessage.h \
    enginebase.h \
    engineinterface.h \
    imessage.h \
    levelgenerator.h \
    levelobjectcreator.h \
    messageanswerdispatcher.h \
    messageheader.h \
    messagenegotiator.h

