#ifndef SCENEBASE_H
#define SCENEBASE_H

#include <QObject>
#include <QQmlComponent>
#include <base/sceneitem.h>
#include <factories/controllerfactory.cpp>
#include <factories/sceneitemsfactory.cpp>
#include <engineinterface.h>

class PLUGINSBASE_EXPORT SceneBase : public QObject
{
    Q_OBJECT

public:
    explicit SceneBase(QObject *parent = nullptr) : QObject(parent) {}
    virtual void addFactory(QList<SceneItemsFactory*> factories) = 0;
    virtual void setEngineInterface(EngineInterface * ei) = 0;

protected:
    SceneItem* getItem(uint32_t id);
    virtual SceneItem *addItem(QPointF pos, QString objectType, uint32_t id) = 0;
    virtual SceneItem *addItem(double x, double y, QString objectType, uint32_t id) = 0;
    virtual void removeItem(SceneItem* item) = 0;

protected:
    QHash<QString, SceneItemsFactory*> m_factoriesHash;
    QHash<QString, ControllerFactory*> m_createdControllers;

};

#endif // SCENEBASE_H
