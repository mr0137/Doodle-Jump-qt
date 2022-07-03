#include "scene.h"

#include <base/sceneitem.h>
#include <messages/changecoordsmsg.h>
#include <messages/createitemmessage.h>
#include <messages/removeitemmessage.h>
#include <messages/setmodeenginemsg.h>

Scene::Scene(QObject *parent)
    : SceneBase(parent)
{
    m_mutex = new QMutex();
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, [this](){
        updateItems();
    });
}

void Scene::addFactory(const QList<SceneItemFactory *> *factories)
{
    for (auto f : *factories)
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

        ei->installStreamMsg<CreateItemMsg>([this](CreateItemMsg msg, uint32_t itemId){
            QMutexLocker locker(m_mutex);
            addItem(QPoint(msg.x, msg.y), msg.objectType, itemId, QVariantMap{{"width", msg.width}, {"height", msg.height}});
        });

        ei->installStreamMsg<RemoveItemMessage>([this](RemoveItemMessage msg, uint32_t itemId){
            QMutexLocker locker(m_mutex);
            if (m_sceneItemsRegistry.contains(itemId))
            {
                auto object = m_sceneItemsRegistry[itemId];
                object->setRemovingState(SceneItem::PREPARE);
            }
        });

        ei->installStreamMsg<ChangeCoordsMsg>([this](ChangeCoordsMsg msg, uint32_t itemId){
            QMutexLocker locker(m_mutex);
            if (m_sceneItemsRegistry.contains(itemId))
            {
                auto object = m_sceneItemsRegistry[itemId];
                object->setX(msg.x);
                object->setY(msg.y);
            }
        });
    }
}

void Scene::startTest()
{
    SetModeEngineMsg startEngineMsg;
    startEngineMsg.mode = EngineMode::START;
    m_engineInterface->sendToEngine(startEngineMsg).onCompleted<SetModeEngineMsgAns>([this](const SetModeEngineMsgAns & ans){
        qDebug() << ":start" << ans.modeChangedSuccess;
         m_timer->start(50);
    });
}

SceneItem *Scene::addItem(QPoint pos, QString objectType, uint32_t id, QVariantMap initialParams)
{
    SceneItem * item = nullptr;
    auto type = objectType;

    if (m_factoriesHash.contains(type))
    {
        QVariantMap m{{"x", pos.x()}, {"y" , pos.y()}};
        for (const QString& str : initialParams.keys())
        {
            m[str] = initialParams[str];
        }
        item = m_factoriesHash[type]->create(m);
        item->setObjectName(objectType);
        item->setParent(this);
        item->setId(id);

        m_sceneItemsRegistry[id] = item;
        m_sceneItems.push_back(item);
    }
    return item;
}

SceneItem *Scene::addItem(double x, double y, QString objectType, uint32_t id)
{
    return addItem(QPoint(x, y), objectType, id);
}

void Scene::removeItem(SceneItem *item)
{
    if (item != nullptr)
    {
        m_sceneItems.removeAll(item);
        item->deleteLater();
    }
}

void Scene::updateItems()
{
    QMutexLocker locker(m_mutex);
    for (int i = m_sceneItems.length() - 1; i >= 0  ; i--)
    {
        if (m_sceneItems[i]->removingState() == SceneItem::READY)
        {
            removeItem(m_sceneItems[i]);
        }
    }
}
