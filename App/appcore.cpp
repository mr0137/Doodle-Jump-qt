#include "appcore.h"
#include <QGuiApplication>

AppCore::AppCore(QObject *parent)
    : QObject{parent},
      m_scene(new Scene(this))
{

}

AppCore *AppCore::getInstance()
{
    static AppCore* m_appcore = nullptr;
    if (!m_appcore)
    {
        m_appcore = new AppCore(qApp);
    }
    return m_appcore;
}

QObject *AppCore::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return getInstance();
}

Scene *AppCore::scene() const
{
    return m_scene;
}

void AppCore::setScene(Scene *newScene)
{
    if (m_scene == newScene)
        return;
    m_scene = newScene;
    emit sceneChanged();
}
