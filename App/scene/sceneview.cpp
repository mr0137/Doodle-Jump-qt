#include "sceneview.h"
#include "scene/background/backgroundnoise.h"
#include <scene/background/backgroundgrid.h>
#include <QPainter>
#include <QSGSimpleTextureNode>
#include <QSGTransformNode>

class BackgroundNode : public QSGNode
{
public:
    BackgroundGrid *grid = nullptr;
    BackgroundNoise *background = nullptr;
};

class ChildNode : public QSGGeometryNode
{
public:
    QSGSimpleTextureNode *texture = nullptr;
    uint32_t id;
};

class MainNode : public QSGNode
{
public:
    //!subchilds
    QMap<uint32_t, ChildNode*> childs;
    //! childs
    BackgroundNode *backgroundNode = nullptr;
    QSGTransformNode *shiftYTransformNode = nullptr;

};

SceneView::SceneView()
{
    setFlag(ItemHasContents, true);
    setFlag(QQuickItem::ItemAcceptsInputMethod, true);
    setFlag(QQuickItem::ItemIsFocusScope, true);
    setClip(true);
    setSmooth(true);
    setAntialiasing(true);
    setAcceptHoverEvents(true);
    forceActiveFocus();
}

QSGNode* SceneView::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    MainNode* mainNode = static_cast<MainNode*>(node);
    //background test display
    if (!mainNode)
    {
        mainNode = new MainNode();
        mainNode->shiftYTransformNode = new QSGTransformNode();
        mainNode->backgroundNode = new BackgroundNode();

        mainNode->appendChildNode(mainNode->backgroundNode);
        mainNode->appendChildNode(mainNode->shiftYTransformNode);

        mainNode->backgroundNode->grid = new BackgroundGrid();
        mainNode->backgroundNode->background = new BackgroundNoise(window());

        mainNode->backgroundNode->appendChildNode(mainNode->backgroundNode->background);
        mainNode->backgroundNode->appendChildNode(mainNode->backgroundNode->grid);
        m_geometryChanged = true;
    }

    QRectF rect = boundingRect();

    if (rect.isEmpty())
    {
        delete mainNode;
        return nullptr;
    }

    if (m_geometryChanged)
    {
        mainNode->backgroundNode->background->setRect(rect);
        mainNode->backgroundNode->grid->setRect(rect);
    }
    for (auto* item : qAsConst(m_scene->m_sceneItems))
    {
        if (item->needUpdate())
        {
            auto child = mainNode->childs[item->id()];
            if (!child)
            {
                child = new ChildNode();
                child->id = item->id();

                child->setGeometry(new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4));
                child->geometry()->setDrawingMode(QSGGeometry::DrawTriangleFan);

                auto m = new QSGFlatColorMaterial();
                m->setColor("green");
                child->setMaterial(m);
                child->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);

                child->texture = new QSGSimpleTextureNode();
                child->texture->setOwnsTexture(true);
                child->appendChildNode(child->texture);
                QImage img(item->width(), item->height(), QImage::Format_ARGB32);
                img.fill(Qt::red);
                auto t = window()->createTextureFromImage(img, QQuickWindow::TextureHasAlphaChannel);
                child->texture->setTexture(t);
                child->texture->setRect(QRectF(item->x(), item->y(), img.width(), img.height()));
                mainNode->shiftYTransformNode->appendChildNode(child);
                mainNode->childs[item->id()] = child;
            }

            if (item->needUpdate())
            {
                auto g = child->geometry();
                g->vertexDataAsPoint2D()[0].set(item->x(), item->y());
                g->vertexDataAsPoint2D()[1].set(item->x() + item->width(), item->y());
                g->vertexDataAsPoint2D()[2].set(item->x() + item->width(), item->y() + item->height());
                g->vertexDataAsPoint2D()[3].set(item->x(), item->y() + item->height());
                child->texture->setRect(QRectF(item->x(), item->y(), item->width(), item->height()));
                child->setGeometry(g);
                child->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);
                item->setNeedUpdate(false);
            }
        }
    }

    if (m_fpsMonitor.isWorking())
    {
        setCurrentFPS(m_fpsMonitor.recalculateFPS());
    }

    m_geometryChanged = false;

    update();
    return mainNode;
}

void SceneView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void SceneView::keyPressEvent(QKeyEvent *event)
{

    QQuickItem::keyPressEvent(event);
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

double SceneView::currentFPS() const
{
    return m_currentFPS;
}

void SceneView::setCurrentFPS(double newCurrentFPS)
{
    if (qFuzzyCompare(m_currentFPS, newCurrentFPS))
        return;
    m_currentFPS = newCurrentFPS;
    emit currentFPSChanged();
}
