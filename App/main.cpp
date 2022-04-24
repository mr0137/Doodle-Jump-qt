#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <appcore.h>
#include "engine.h"

#include <scene/sceneview.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterSingletonInstance("App", 1, 0, "AppCore", AppCore::getInstance());
    qmlRegisterUncreatableType<Scene>("App", 1, 0, "Scene", "one instance per programm");
    qmlRegisterType<SceneView>("App", 1, 0, "SceneView");

    auto coreEngine = new Engine();
    //! [additional]

    coreEngine->start();
    QObject::connect(&app, &QGuiApplication::aboutToQuit, coreEngine, &Engine::stop);

    auto ei = coreEngine->getInterface();
    qmlRegisterType<QObject>("KLib", 1, 0, "Null");

    AppCore::getInstance()->scene()->setEngineInterface(ei);

    QQmlApplicationEngine appEngine;
    //auto engine = static_cast<QQmlEngine*>(&appEngine);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&appEngine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    appEngine.load(url);

    return app.exec();
}
