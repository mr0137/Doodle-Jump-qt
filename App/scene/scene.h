#ifndef SCENE_H
#define SCENE_H

#include <engineinterface.h>
#include <base/scenebase.h>

class Scene : public SceneBase
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addFactory(QList<SceneItemsFactory *> factories) override;
    void setEngineInterface(EngineInterface * ei) override;

protected:
    SceneItem *addItem(QPointF pos, QString objectName, uint32_t id) override;
    SceneItem *addItem(double x, double y, QString type, uint32_t id) override;
    void removeItem(SceneItem *item) override;
private:
    EngineInterface *m_engineInterface = nullptr;
};

#endif // SCENE_H
