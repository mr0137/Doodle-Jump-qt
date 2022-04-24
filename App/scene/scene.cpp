#include "scene.h"

#include <base/sceneitem.h>
#include <base/global_messages/createitemmessage.h>
#include <base/global_messages/removeitemmessage.h>

Scene::Scene(QObject *parent)
    : SceneBase(parent)
{

}

void Scene::addFactory(QList<SceneItemsFactory *> factories)
{

}

void Scene::setEngineInterface(EngineInterface *ei)
{
    if(ei != nullptr){
        m_engineInterface = ei;
        ei->installStreamMsg<CreateItemMsg>([this](CreateItemMsg msg, int itemId){
            SceneItem *item = nullptr;
            item = addItem(QPointF(msg.x, msg.y), msg.objectType, itemId);
            return item;
        });
        ei->installStreamMsg<RemoveItemMessage>([this](RemoveItemMessage msg, int itemId){

        });
    }
}

SceneItem *Scene::addItem(QPointF pos, QString objectType, uint32_t id)
{

}

SceneItem *Scene::addItem(double x, double y, QString objectType, uint32_t id)
{

}

void Scene::removeItem(SceneItem *item)
{

}
