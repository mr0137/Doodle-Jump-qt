#ifndef ISCENEITEMINTERFACE_H
#define ISCENEITEMINTERFACE_H

#include <AbstractPluginInterface.h>
#include <pluginsbase_global.h>
#include <base/sceneitem.h>
#include <factories/controllerfactory.h>
#include <factories/sceneitemsfactory.h>

class SceneItemsFactory;
class ControllerFactory;
class PLUGINSBASE_EXPORT ISceneItem : public AbstractPluginInterface
{
public:
    ISceneItem();
    ~ISceneItem();
    QList<SceneItemsFactory*> getSceneItemsFactories() { return creators; }
    QList<ControllerFactory*> getControllerFactories() { return controllers; }
    template<class T> void createItemFactory();
    template<class T> void createControllerFactory();
    virtual void init(Engine *, QString appPath = "", const QVariantList &depencies = QVariantList()) override { Q_UNUSED(appPath)};
    virtual ComponentsMap getComponents() override { return {}; };
signals:

private:
    QList<SceneItemsFactory *> creators;
    QList<ControllerFactory *> controllers;
};

template<class T>
        void ISceneItem::createItemFactory()
{
    assert (!typeName().isEmpty());
    auto f = new SceneItemsFactory([]()->SceneItem*{ return new T();});
    f->setObjectName(typeName());
    creators.push_back(f);
}

template<class T>
        void ISceneItem::createControllerFactory()
{
    assert (!typeName().isEmpty());
    auto cf = new ControllerFactory([]()->AbstractObjectController*{ return new T();});
    cf->setObjectName(typeName());
    controllers.push_back(cf);
}
Q_DECLARE_INTERFACE(ISceneItem, "ISceneItem")
#endif // ISCENEITEMINTERFACE_H
