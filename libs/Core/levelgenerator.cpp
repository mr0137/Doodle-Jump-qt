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
        for (int i = 10; i < 1300; i+=40)
        {
            for (int j = 0; j < 750; j+=110)
            createObject("SlabVMoving", {j, i});
        }

        for (int i = 100; i < 1200; i+=40)
        {
            for (int j = 0; j < 750; j+=110)
            createObject("SlabHMoving", {j, i});
        }

        //for (int i = 0; i < 5; i++)
        //{
        //    createObject("SlabVMoving", {130, 900 + i*100});
//
//
        //    createObject("SlabHMoving", {130, 300 + i*100});
        //    createObject("SlabVMoving", {130, 950 + i*100});
        //    createObject("SlabHMoving", {130, 350 + i*100});
        //    createObject("SlabVMoving", {130, 1000 + i*100});
        //    createObject("SlabHMoving", {130, 400 + i*100});
//
        //    createObject("SlabVMoving", {330, 900 + i*100});
        //    createObject("SlabHMoving", {330, 300 + i*100});
        //    createObject("SlabVMoving", {330, 950 + i*100});
        //    createObject("SlabHMoving", {330, 350 + i*100});
        //    createObject("SlabVMoving", {330, 1000 + i*100});
        //    createObject("SlabHMoving", {330, 400 + i*100});
//
        //    createObject("SlabVMoving", {480, 900 + i*100});
        //    createObject("SlabHMoving", {480, 300 + i*100});
        //    createObject("SlabVMoving", {480, 950 + i*100});
        //    createObject("SlabHMoving", {480, 350 + i*100});
        //    createObject("SlabVMoving", {480, 1000 + i*100});
        //    createObject("SlabHMoving", {480, 400 + i*100});
        //}

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
    m_createHandler(type, pos);
}
