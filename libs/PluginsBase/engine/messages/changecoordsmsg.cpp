#include "changecoordsmsg.h"
#include <QDataStream>

void ChangeCoordsMsg::serialize(QDataStream *s) const
{
    *s << this->x << this->y;
}

void ChangeCoordsMsg::deserialize(QDataStream * s)
{
    *s >> this->x >> this->y;
}

void ChangeCoordsMsgAns::serialize(QDataStream * s) const
{;
    *s << this->success;
}

void ChangeCoordsMsgAns::deserialize(QDataStream * s)
{
    *s >> this->success;
}
