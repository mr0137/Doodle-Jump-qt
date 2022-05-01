#ifndef ABSTRACTPLUGININTERFACE_H
#define ABSTRACTPLUGININTERFACE_H

#include "pluginsbase_global.h"
#include <QHash>
#include <QList>
#include <QObject>
#include <QVariantList>
#include <enginebase.h>
#include "factories/sceneitemfactory.h"
#include "factories/controllerfactory.h"

class PLUGINSBASE_EXPORT AbstractPluginInterface
{
public:
    AbstractPluginInterface() {}
    virtual ~AbstractPluginInterface() {}

    virtual void init(EngineBase * engine, QString appPath = "") = 0;

    QString typeName() { return m_typeName; }
    //TODO: rewrite to shared_ptr
    const QList<SceneItemFactory*> *getSceneItemFactories() { return &m_creators; }
    const QList<ControllerFactory*> *getControllerFactories() { return &m_controllers; }
    const QList<ControllerFactory*> *getCollideControllerFactories() { return &m_collideControllers; }
    QHash<QString, QString> getResources() { return m_resources; }
protected:
    template<typename Msg, typename Callable>
    void registerPluginEngineCallback(EngineBase*, Callable f);

    template<class T>
    void createObjectFactory();

    template<class T>
    void createControllerFactory();

protected:
    QString m_typeName;
    QHash<QString, QString> m_resources;
    QList<SceneItemFactory *> m_creators;
    QList<ControllerFactory *> m_controllers;
    QList<ControllerFactory *> m_collideControllers;
};

template<typename Msg, typename Callable>
void AbstractPluginInterface::registerPluginEngineCallback(EngineBase * engine, Callable f)
{
    if (engine)
    {
        engine->getInterface()->addConnection<Msg>(f);
    }
}

template<class T>
void AbstractPluginInterface::createObjectFactory()
{
    auto factory = new SceneItemFactory(typeid(T).name(), []()->SceneItem*{ return new T();});
    m_creators.push_back(factory);
}

template<class T>
void AbstractPluginInterface::createControllerFactory()
{
    auto factory = new ControllerFactory(typeid(T).name(), []()->AbstractObjectController*{ return new T();});
    m_controllers.push_back(factory);
}

Q_DECLARE_INTERFACE(AbstractPluginInterface, "com.my.AbstractPluginInterface")

#endif // ABSTRACTPLUGININTERFACE_H
