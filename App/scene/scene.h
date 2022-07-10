#ifndef SCENE_H
#define SCENE_H

#include <QMutex>
#include <QTimer>
#include <engineinterface.h>
#include <base/scenebase.h>
#include "keynegotiator.h"

class Scene : public SceneBase
{
    Q_OBJECT
    friend class SceneView;
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
    void addFactory(const QList<SceneItemFactory *> *factories) override;
    void setEngineInterface(EngineInterface * ei) override;
    void setKeyNegotiator(KeyNegotiator* keyNegotiator);
    void startTest();

protected:
    SceneItem *addItem(QPoint pos, QString objectName, uint32_t id, QVariantMap initialParams = {}) override;
    SceneItem *addItem(double x, double y, QString type, uint32_t id) override;
    void removeItem(SceneItem *item) override;

private:
    void updateItems();

private:
    QMutex* m_mutex;
    QTimer* m_timer = nullptr;
    EngineInterface* m_engineInterface = nullptr;
    KeyNegotiator* m_keyNegotiator = nullptr;
    QList<SceneItem*> m_sceneItems;
    QMap<uint32_t, SceneItem*> m_sceneItemsRegistry;
    uint32_t m_doodlerId = -1;
};

#endif // SCENE_H
