QT -= gui
QT += concurrent
QT += core
TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractobjectcontroller.cpp \
    basemovecontroller.cpp \
    emptymessage.cpp \
    engine.cpp \
    engineinterface.cpp \
    imesssage.cpp \
    itemsfactory.cpp \
    kcirclebuffer.cpp \
    messageanswerdispatcher.cpp \
    messagebase.cpp \
    messageheader.cpp \
    messagenegotiator.cpp

HEADERS += \
    abstractobjectcontroller.h \
    basemovecontroller.h \
    core_global.h \
    emptymessage.h \
    engine.h \
    engineinterface.h \
    imesssage.h \
    itemsfactory.h \
    kcirclebuffer.h \
    messageanswerdispatcher.h \
    messagebase.h \
    messageheader.h \
    messagenegotiator.h

