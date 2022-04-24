TEMPLATE = lib
TARGET = pluginsbase
QT -= gui
QT += quick
QT += core
CONFIG += c++17
CONFIG += shared dll

CONFIG(release, debug|release){
DESTDIR = $$PWD/../../bin/libs/
}

#Inputs
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PLUGINSBASE_LIBRARY
SOURCES += \
        base/scenebase.cpp \
        engine/messages/changecoordsmsg.cpp \
        factories/controllerfactory.cpp \
        factories/sceneitemsfactory.cpp \
        iphysicalitem.cpp \
        base/sceneitem.cpp \
        AbstractPluginInterface.cpp \
        tools/globalconfig.cpp

HEADERS += \
        base/scenebase.h \
        engine/messages/changecoordsmsg.h \
        factories/controllerfactory.h \
        factories/sceneitemsfactory.h \
        iphysicalitem.h \
        pluginsbase_global.h \
        tools/globalconfig.h \
        base/sceneitem.h \
        tools/pluginloader.h \
        AbstractPluginInterface.h

CONFIG(release, debug|release){
LIBS += -L$$PWD/../../../bin/libs/ -lcore
}else{
win32: LIBS += -L$$OUT_PWD/../core/debug -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore
}

INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

