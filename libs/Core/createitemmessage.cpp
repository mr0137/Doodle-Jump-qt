#include "createitemmessage.h"
#include <QDataStream>

void CreateItemMsg::serialize(QDataStream * s) const
{
    *s << id << x << y << objectType;
}

void CreateItemMsg::deserialize(QDataStream *s)
{
    *s >> id >> x >> y >> objectType;
}

void CreateItemMsgAns::serialize(QDataStream * s) const
{
    *s << id << objectType;
}

void CreateItemMsgAns::deserialize(QDataStream *s)
{
    *s >> id >> objectType;
}