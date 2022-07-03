#include "levelgenerator.h"
#include "engineinterface.h"

LevelGenerator::LevelGenerator()
{

}

LevelGenerator::~LevelGenerator()
{

}

void LevelGenerator::proceed(QRect visualRect)
{
    static int i = 0;
    if (i++ == 0)
    {
        for (int i = 0; i < 1; i++)
        {
            createObject("Slab", {130, 700 + i*100});
            //createObject("SlabVMoving", {530, 500 + i*100});
            createObject("SlabVMoving", {130, 900 + i*100});
            createObject("SlabHMoving", {130, 300 + i*100});
        }

    }
}

void LevelGenerator::addGenerateableObjectsTypes(AbstractObjectController *objectTypes, ControllerType controllerType)
{
    switch(controllerType)
    {
    case ControllerType::SLAB:
    {
        m_creatableSlabObjects.append(objectTypes);
        break;
    }
    case ControllerType::MONSTER:
    {
        m_creatableMonsterObjects.append(objectTypes);
        break;
    }
    case ControllerType::DOODLER:
    {
        qDebug() << "Cannot add Doodler to levelGenerator";
        return;
    }
    case ControllerType::GHOST:
    {
        qDebug() << "Cannot add Doodler to levelGenerator";
        return;
    }
    case ControllerType::BULLET:
    {
        qDebug() << "Cannot add Doodler to levelGenerator";
        return;
    }
    case ControllerType::POWERUP:
    {
        m_creatablePowerUPObjects.append(objectTypes);
        break;
    }
    }
}

void LevelGenerator::setCreateHandler(const std::function<uint32_t (QString, QPoint)> &createHandler)
{
    m_createHandler = createHandler;
}

void LevelGenerator::setDeleteHandler(const std::function<bool(uint32_t)> &deleteHandler)
{
    m_deleteHandler = deleteHandler;
}

void LevelGenerator::createObject(QString type, QPoint pos)
{
    auto id = m_createHandler(type, pos);
}
