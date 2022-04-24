#include "scene.h"

#include <base/sceneitem.h>
#include <createitemmessage.h>
#include <removeitemmessage.h>
#include <setmodeenginemsg.h>

Scene::Scene(QObject *parent)
    : SceneBase(parent)
{

}

void Scene::addFactory(QList<SceneItemsFactory *> factories)
{
    for (auto f : factories)
    {
        qDebug() << f->type();
        if (!m_factoriesHash.keys().contains(f->type()))
            m_factoriesHash.insert(f->type(), f);
    }
}

void Scene::setEngineInterface(EngineInterface *ei)
{
    if(ei != nullptr){
        m_engineInterface = ei;
        ei->installStreamMsg<CreateItemMsg>([this](CreateItemMsg msg, int itemId){
            addItem(QPointF(msg.x, msg.y), msg.objectType, itemId);
        });
        ei->installStreamMsg<RemoveItemMessage>([this](RemoveItemMessage msg, int itemId){

        });
    }
}

void Scene::startTest()
{
    SetModeEngineMsg startEngineMsg;
    startEngineMsg.mode = EngineMode::START;
    m_engineInterface->sendToEngine(startEngineMsg).onCompleted<SetModeEngineMsgAns>([this](const SetModeEngineMsgAns & ans){
        qDebug() << ":start" << ans.modeChangedSuccess;
    });
}

SceneItem *Scene::addItem(QPointF pos, QString objectType, uint32_t id)
{
    SceneItem * item = nullptr;
    auto type = objectType;

    if (m_factoriesHash.keys().contains(type)){
        QVariantMap m{{"x", pos.x()}, {"y" , pos.y()}};
        item = m_factoriesHash[type]->create(m);
        item->setObjectName(objectType);
        item->setParent(this);
        item->setId(id);

        m_sceneItemsList.push_back(item);
    }
    return item;
}

SceneItem *Scene::addItem(double x, double y, QString objectType, uint32_t id)
{
    return addItem(QPointF(x, y), objectType, id);
}

void Scene::removeItem(SceneItem *item)
{

}
