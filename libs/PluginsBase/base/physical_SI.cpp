#include "physical_SI.h"

PhysicalItem::PhysicalItem(QObject *parent) : SceneItem(parent)
{
    setType("PhisycalItem");
}

void PhysicalItem::move(QPointF pos)
{
    //setX(pos.x());
    //setY(pos.y());
    coordsUpdated(pos);
}

