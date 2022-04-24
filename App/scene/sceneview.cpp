#include "sceneview.h"
#include "scene/background/backgroundnoise.h"
#include <scene/background/backgroundgrid.h>

class GraphNode : public QSGNode
{
public:
    BackgroundGrid *grid = nullptr;
    BackgroundNoise *background = nullptr;
};

SceneView::SceneView()
{
    setFlag(ItemHasContents, true);
}

QSGNode *SceneView::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    //background test display
    GraphNode *n = static_cast<GraphNode *>(node);

    QRectF rect = boundingRect();

    if (rect.isEmpty())
    {
        delete n;
        return nullptr;
    }

    if (!n)
    {
        n = new GraphNode();

        n->grid = new BackgroundGrid();
        n->background = new BackgroundNoise(window());

        n->appendChildNode(n->background);
        n->appendChildNode(n->grid);
        m_geometryChanged = true;
    }

    if (m_geometryChanged) {
        n->background->setRect(rect);
        n->grid->setRect(rect);
    }

    m_geometryChanged = false;
    update();
    return n;
}

void SceneView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

Scene *SceneView::scene() const
{
    return m_scene;
}

void SceneView::setScene(Scene *newScene)
{
    if (m_scene == newScene)
        return;
    m_scene = newScene;
    emit sceneChanged();
}
