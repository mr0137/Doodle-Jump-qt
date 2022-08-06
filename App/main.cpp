#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <appcore.h>
#include "engine.h"
#include <QtQml>
#include <scene/sceneview.h>

static int jj = 0;
double rec(double y, double delta)
{   jj++;
    if (y <= 0)
    {
        return delta;
    }
    delta += 0.0000098 * 1000;
    return rec(y - delta, delta);
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    auto res = rec(400.644, 0);
    qDebug() << jj << res;

    //disables vsync for any QtQuick windows we create (BUG 406180)
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(format);

    qmlRegisterSingletonInstance<AppCore>("App", 1, 0, "AppCore", AppCore::getInstance());
    qmlRegisterUncreatableType<Scene>("App", 1, 0, "Scene", "one instance per programm");
    qmlRegisterType<SceneView>("App", 1, 0, "SceneView");

    QObject::connect(&app, &QGuiApplication::aboutToQuit, &app, [&](){
        AppCore::getInstance()->stop();
    });

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
