#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QQuickItem>
#include "fpsmonitor.h"
#include "scene.h"

class SceneView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)
    Q_PROPERTY(double currentFPS READ currentFPS WRITE setCurrentFPS NOTIFY currentFPSChanged)
public:
    SceneView();

    Scene *scene() const;
    void setScene(Scene *newScene);

    double currentFPS() const;
    void setCurrentFPS(double newCurrentFPS);

signals:
    void sceneChanged();

    void currentFPSChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    Scene* m_scene = nullptr;
    bool m_geometryChanged = true;
    double m_currentFPS;
    FpsMonitor m_fpsMonitor;
};

#endif // SCENEVIEW_H
