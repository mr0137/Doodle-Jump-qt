#include "appcore.h"
#include <QGuiApplication>

#include "slabdefault.h"

AppCore::AppCore(QObject *parent)
    : QObject{parent},
      m_scene(new Scene(this))
{
    auto testFactory = new SceneItemsFactory("SlabDefault", []() -> SceneItem*{ return new SlabDefault(); });
    m_scene->addFactory({testFactory});
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

QObject *AppCore::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngineBase)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngineBase)
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

void AppCore::start()
{
    m_scene->startTest();
}
