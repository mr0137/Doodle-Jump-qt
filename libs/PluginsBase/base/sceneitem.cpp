#include "sceneitem.h"

SceneItem::SceneItem(QObject *parent) : QObject(parent)
{

}

QString SceneItem::type() const
{
    return m_type;
}

void SceneItem::setType(const QString &newType)
{
    m_type = newType;
}

uint32_t SceneItem::id() const
{
    return m_id;
}

double SceneItem::x() const
{
    return m_x;
}

double SceneItem::y() const
{
    return m_y;
}

double SceneItem::width() const
{
    return m_width;
}

double SceneItem::height() const
{
    return m_height;
}

const QString &SceneItem::imagePath() const
{
    return m_imagePath;
}

SceneItem::RemovingState SceneItem::removeState()
{
    return m_removingState;
}

QRectF SceneItem::boundingRect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}

void SceneItem::setId(uint32_t newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

void SceneItem::setX(double newX)
{
    if (qFuzzyCompare(m_x, newX))
        return;
    m_x = newX;
    emit xChanged();
}

void SceneItem::setY(double newY)
{
    if (qFuzzyCompare(m_y, newY))
        return;
    m_y = newY;
    emit yChanged();
}
