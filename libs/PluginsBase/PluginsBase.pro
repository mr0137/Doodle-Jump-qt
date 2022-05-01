TEMPLATE = lib
TARGET = pluginsbase
QT -= gui
QT += quick
QT += core
CONFIG += c++20
CONFIG += shared dll

CONFIG(release, debug|release){
DESTDIR = $$PWD/../../bin/libs/
}

#Inputs
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PLUGINSBASE_LIBRARY
SOURCES += \
        base/scenebase.cpp \
        factories/controllerfactory.cpp \
        factories/sceneitemfactory.cpp \
        base/sceneitem.cpp \
        AbstractPluginInterface.cpp \
        messages/changecoordsmsg.cpp \
        messages/createitemmessage.cpp \
        messages/removeitemmessage.cpp \
        messages/setmodeenginemsg.cpp \
        tools/globalconfig.cpp \
        tools/pluginloader.cpp

HEADERS += \
        base/scenebase.h \
        factories/controllerfactory.h \
        factories/sceneitemfactory.h \
        messages/changecoordsmsg.h \
        messages/createitemmessage.h \
        messages/removeitemmessage.h \
        messages/setmodeenginemsg.h \
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

