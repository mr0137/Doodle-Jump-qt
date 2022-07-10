#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <appcore.h>
#include "engine.h"
#include <QtQml>
#include <scene/sceneview.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //qmlRegisterSingletonType("App", 1, 0, "AppCore", [](QQmlEngine *engine, QJSEngine *scriptEngineBase) -> QObject* { return AppCore::qmlInstance(engine, scriptEngineBase);});
    //qmlRegisterUncreatableType("App", 1, 0, "AppCore", "Singleton");
    qmlRegisterSingletonInstance("App", 1, 0, "AppCore", AppCore::getInstance());
    qmlRegisterUncreatableType<Scene>("App", 1, 0, "Scene", "one instance per programm");
    qmlRegisterType<SceneView>("App", 1, 0, "SceneView");

    QObject::connect(&app, &QGuiApplication::aboutToQuit, &app, [&](){
        AppCore::getInstance()->stop();
    });

    //auto ei = coreEngine->getInterface();
    qmlRegisterType<QObject>("KLib", 1, 0, "Null");

    AppCore::getInstance()->init(QString(argv[0]));

    QQmlApplicationEngine appEngine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&appEngine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    appEngine.load(url);

    return app.exec();
}
