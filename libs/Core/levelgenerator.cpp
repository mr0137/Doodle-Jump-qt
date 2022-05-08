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
        createObject("Slab", {0, 30});


                //this.data.push([random(5,370),random(300,400),1,0,0,0]);
                //this.data.push([random(5,370),random(100,200),1,0,0,0]);
                //this.data.push([random(5,370),random(100,300),1,0,0,0]);
                //this.data.push([random(5,370),random(0,50),1,0,0,0]);
                //this.data.push([random(5,370),random(0,-50),1,0,0,0]);
                //this.data.push([random(5,370),random(-40,-200),1,0,0,0]);
                //this.data.push([random(5,370),random(0,300),1,0,0,0]);

                //CreateItemMsg msg;
        //msg.id = 10;
        //msg.x = 0;
        //msg.y = 1300;
        //msg.objectType = "SlabDefault";
        //m_engineInterface->sendFromEngine(msg, 10);
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
