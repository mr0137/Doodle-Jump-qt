#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <QList>
#include <QMap>
#include <functional>
#include "abstractobjectcontroller.h"
#include "core_global.h"

class EngineInterface;

class CORE_EXPORT LevelGenerator
{
public:
    LevelGenerator();
    ~LevelGenerator();
    void proceed(const QRectF &visualRect);
    void addGenerateableObjectsTypes(AbstractObjectController* objectTypes, ControllerType controllerType);

    void setCreateHandler(const std::function<uint32_t (QString, QPointF)> &createHandler);
    void setDeleteHandler(const std::function<bool(uint32_t)> &deleteHandler);
private:
    void createObject(QString type, QPointF pos);
private:
    std::function<uint32_t(QString type, QPointF)> m_createHandler = nullptr;
    std::function<bool(uint32_t)> m_deleteHandler = nullptr;

    QList<AbstractObjectController*> m_creatableSlabObjects;
    QList<AbstractObjectController*> m_creatableMonsterObjects;
    QList<AbstractObjectController*> m_creatablePowerUPObjects;

    QMap<uint32_t, AbstractObjectController*> m_createdControllers;
};

#endif // LEVELGENERATOR_H
