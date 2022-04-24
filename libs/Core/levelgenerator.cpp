#include "levelgenerator.h"
#include "createitemmessage.h"
#include "engineinterface.h"

LevelGenerator::LevelGenerator(EngineInterface *interface) : m_engineInterface(interface)
{

}

void LevelGenerator::proceed()
{
    static int i = 0;
    if (i++ == 0)
    {
        CreateItemMsg msg;
        msg.id = 10;
        msg.x = 100;
        msg.y = 100;
        msg.objectType = "SlabDefault";
        m_engineInterface->sendFromEngine(msg, 10);
    }
}
