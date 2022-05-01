#ifndef LEVELOBJECTCREATOR_H
#define LEVELOBJECTCREATOR_H

#include "abstractobjectcontroller.h"
#include <cstdint>
class EngineInterface;
//base class for generatin data
struct LevelObjectCreator
{
    ControllerType controllerType;
    std::string objectType;
    uint32_t controllerId;
    int x;
    int y;
    virtual void generate(EngineInterface *engineInterface) = 0;
};

#endif // LEVELOBJECTCREATOR_H
