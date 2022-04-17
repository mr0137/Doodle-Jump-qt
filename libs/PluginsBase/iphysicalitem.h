#ifndef IPHYSICALITEM_H
#define IPHYSICALITEM_H

#include "AbstractPluginInterface.h"

#include <QString>
#include <QQmlEngine>
#include <QQmlContext>
#include <engine.h>
#include <pluginsbase_global.h>
#include <base/sceneitem.h>
#include <factories/controllerfactory.h>
#include <factories/sceneitemsfactory.h>

class SceneItemsFactory;
class ControllerFactory;

class PLUGINSBASE_EXPORT IPhysicalItem : public AbstractPluginInterface
{
public:
    IPhysicalItem();
    QList<SceneItemsFactory*> getSceneItemsFactories() {return m_creators;}
    QList<ControllerFactory*> getControllerFactories() {return m_controllers;}
    virtual QStringList creatableTypes() { return {}; }
    template<class T> void createItemFactory();
    template<class T> void createControllerFactory();
    ~IPhysicalItem();
private:
    QList<SceneItemsFactory *> m_creators;
    QList<ControllerFactory *> m_controllers;
};

template<class T>
void IPhysicalItem::createItemFactory()
{
    assert (!typeName().isEmpty());
    auto f = new SceneItemsFactory([]()->SceneItem*{ return new T();});
    f->setObjectName(typeName());
    //TODO : fix path
//    f->setComponentsMap(m);
    m_creators.push_back(f);
}

template<class T>
void IPhysicalItem::createControllerFactory()
{
    assert (!typeName().isEmpty());
    auto cf = new ControllerFactory([]()->AbstractObjectController*{ return new T();});
    cf->setObjectName(typeName());
    m_controllers.push_back(cf);
}
Q_DECLARE_INTERFACE(IPhysicalItem, "com.my.IPhysicalItem")

#endif // IPHYSICALITEM_H
