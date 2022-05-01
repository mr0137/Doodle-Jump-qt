#include "levelgenerator.h"
#include "engineinterface.h"

LevelGenerator::LevelGenerator()
{

}

void LevelGenerator::proceed(Rect visualRect)
{
    //static int i = 0;
    //if (i++ == 0)
    //{
    //    CreateItemMsg msg;
    //    msg.id = 10;
    //    msg.x = 0;
    //    msg.y = 1300;
    //    msg.objectType = "SlabDefault";
    //    m_engineInterface->sendFromEngine(msg, 10);

    //}
}

void LevelGenerator::addCreators(const std::vector<LevelObjectCreator*> &list)
{
    m_creators = list;
}

void LevelGenerator::setCreateHandler(const std::function<uint32_t(std::string)> &createHandler)
{
    m_createHandler = createHandler;
}

void LevelGenerator::setDeleteHandler(const std::function<bool(uint32_t)> &deleteHandler)
{
    m_deleteHandler = deleteHandler;
}
