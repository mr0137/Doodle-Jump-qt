#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QQuickItem>
#include "scene.h"

class SceneView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)
public:
    SceneView();

    Scene *scene() const;
    void setScene(Scene *newScene);

signals:
    void sceneChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
private:
    Scene* m_scene = nullptr;
    bool m_geometryChanged = true;
};

#endif // SCENEVIEW_H
