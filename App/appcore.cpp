#include "appcore.h"
#include "engine.h"
#include <AbstractPluginInterface.h>
#include <QGuiApplication>
#include <tools/pluginloader.h>

AppCore::AppCore(QObject *parent)
    : QObject{parent},
      m_scene(new Scene(this)),
      m_engine(new Engine())
{
    m_scene->setEngineInterface(m_engine->getInterface());
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

AppCore::~AppCore()
{
    m_engine->stop();
    delete m_engine;
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

void AppCore::init(QString appPath)
{
    QString result = appPath;

#ifdef Q_OS_LINUX
    int times = 3;
#endif
#ifdef Q_OS_WINDOWS
    int times = 4;
#endif

    while(times > 0 && !result.isEmpty()){
#ifdef Q_OS_LINUX
        if (result.endsWith("/")) times--;
#endif
#ifdef Q_OS_WINDOWS
        if (result.endsWith("\\")) times--;
#endif
        result.chop(1);
    }
    m_pluginLoader = new PluginLoader(result, this);

    m_pluginLoader->load("CorePlugin");
}

void AppCore::start()
{
    m_engine->start();
    m_scene->startTest();
}

void AppCore::load(QObject *pluginInstance)
{
    if (m_engine != nullptr)
    {
        return;
    }

    auto pluginInterface = reinterpret_cast<AbstractPluginInterface*>(pluginInstance);

    if (pluginInterface)
    {
        m_engine->addCollideControllerFactories(pluginInterface->getControllerFactories());
        m_scene->addFactory(pluginInterface->getSceneItemFactories());
    }
}
