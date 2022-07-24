#include "changeviewrect.h"

void ChangeViewRectMsg::serialize(QDataStream *s) const
{
    *s << y;
}

void ChangeViewRectMsg::deserialize(QDataStream * s)
{
    *s >> y;
}

void ChangeViewRectMsgAns::serialize(QDataStream * s) const
{;
    *s << success;
}

void ChangeViewRectMsgAns::deserialize(QDataStream * s)
{
    *s >> success;
}
