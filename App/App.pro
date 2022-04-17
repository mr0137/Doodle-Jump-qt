QT += quick
QT += core

SOURCES += \
        appcore.cpp \
        main.cpp \
        scene/background/backgroundgrid.cpp \
        scene/background/backgroundnoise.cpp \
        scene/scene.cpp \
        scene/sceneview.cpp

RESOURCES += resources/qml.qrc

QML_IMPORT_PATH =

HEADERS += \
    appcore.h \
    scene/background/backgroundgrid.h \
    scene/background/backgroundnoise.h \
    scene/scene.h \
    scene/sceneview.h


