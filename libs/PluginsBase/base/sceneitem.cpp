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
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

int SceneItem::sceneID() const
{
    return m_sceneID;
}

void SceneItem::setSceneID(int newSceneID)
{
    if (m_sceneID == newSceneID)
        return;
    m_sceneID = newSceneID;
    emit sceneIDChanged();
}
