#include "createitemmsg.h"

CreateItemMsg::CreateItemMsg()
{

}

void CreateItemMsg::serialize(QDataStream *s) const
{
    *s << position[0] << position[1] << position[2] << id << controllerId << velocity << angle << (int)typeOfObject.size() << typeOfObject.c_str() << (int)color.size() << color.c_str();
}

void CreateItemMsg::deserialize(QDataStream *s)
{
    int length;
    *s >> position[0] >> position[1] >> position[2] >> id >> controllerId >> velocity >> angle >> length;
    typeOfObject.reserve(length);
    s->readRawData(&typeOfObject[0], length);
    *s >> length;
    color.reserve(length);
    s->readRawData(&color[0], length);
}
