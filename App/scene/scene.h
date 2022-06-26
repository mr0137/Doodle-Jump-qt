#ifndef SCENE_H
#define SCENE_H

#include <QMutex>
#include <QTimer>
#include <engineinterface.h>
#include <base/scenebase.h>

class Scene : public SceneBase
{
    Q_OBJECT
    friend class SceneView;
public:
    explicit Scene(QObject *parent = nullptr);
    void addFactory(const QList<SceneItemFactory *> *factories) override;
    void setEngineInterface(EngineInterface * ei) override;

    void startTest();

protected:
    SceneItem *addItem(QPoint pos, QString objectName, uint32_t id) override;
    SceneItem *addItem(double x, double y, QString type, uint32_t id) override;
    void removeItem(SceneItem *item) override;

private:
    void updateItems();

private:
    QMutex *m_mutex;
    QTimer *m_timer = nullptr;
    EngineInterface *m_engineInterface = nullptr;
    QList<SceneItem*> m_sceneItems;
    QMap<uint32_t, SceneItem*> m_sceneItemsRegistry;
};

#endif // SCENE_H
