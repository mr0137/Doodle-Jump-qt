#include "levelgenerator.h"
#include "engineinterface.h"

LevelGenerator::LevelGenerator()
{

}

LevelGenerator::~LevelGenerator()
{

}

void LevelGenerator::proceed(QRectF visualRect)
{
    static int i = 0;
    if (i++ == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            if (i == -1)
            {
                createObject("SlabVMoving", {i * 100 + 8.3 * i, visualRect.height() - 30});
            }
            else
            {
                createObject("Slab", {i * 100 + 8.3 * i, visualRect.height() - 30});
            }
        }
        createObject("Doodler", {424, 667});
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

void LevelGenerator::setCreateHandler(const std::function<uint32_t (QString, QPointF)> &createHandler)
{
    m_createHandler = createHandler;
}

void LevelGenerator::setDeleteHandler(const std::function<bool(uint32_t)> &deleteHandler)
{
    m_deleteHandler = deleteHandler;
}

void LevelGenerator::createObject(QString type, QPointF pos)
{
    m_createHandler(type, pos);
}
