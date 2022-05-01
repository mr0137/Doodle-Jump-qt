#include "changecoordsmsg.h"
#include <QDataStream>

void ChangeCoordsMsg::serialize(QDataStream *s) const
{
    *s << id << x << y << id;
}

void ChangeCoordsMsg::deserialize(QDataStream * s)
{
    *s >> id >> x >> y;
}

void ChangeCoordsMsgAns::serialize(QDataStream * s) const
{;
    *s << id << success;
}

void ChangeCoordsMsgAns::deserialize(QDataStream * s)
{
    *s >> id >> success;
}
