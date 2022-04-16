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
        AbstractServerInterface.cpp \
        base/global_messages/createpimsg.cpp \
        base/global_messages/removeitemmessage.cpp \
        base/global_messages/setmodeenginemsg.cpp \
        base/physical_SI.cpp \
        base/scenebase.cpp \
        engine/messages/changecoordsmsg.cpp \
        engine/messages/createitemmsg.cpp \
        engine/messages/itemstartmsg.cpp \
        factories/controllerfactory.cpp \
        factories/sceneitemsfactory.cpp \
        iphysicalitem.cpp \
        isceneiteminterface.cpp \
        base/sceneitem.cpp \
        AbstractPluginInterface.cpp \
        tools/globalconfig.cpp

HEADERS += \
        AbstractServerInterface.h \
        base/global_messages/createpimsg.h \
        base/global_messages/removeitemmessage.h \
        base/global_messages/setmodeenginemsg.h \
        base/physical_SI.h \
        base/scenebase.h \
        engine/messages/changecoordsmsg.h \
        engine/messages/createitemmsg.h \
        engine/messages/itemstartmsg.h \
        factories/controllerfactory.h \
        factories/sceneitemsfactory.h \
        iphysicalitem.h \
        isceneiteminterface.h \
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

