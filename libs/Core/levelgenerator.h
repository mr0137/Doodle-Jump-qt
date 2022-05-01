#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <functional>
#include "abstractobjectcontroller.h"

class EngineInterface;

class LevelGenerator
{
public:
    LevelGenerator(EngineInterface *interface);
    void proceed();
private:
    EngineInterface *m_engineInterface;

};

#endif // LEVELGENERATOR_H
