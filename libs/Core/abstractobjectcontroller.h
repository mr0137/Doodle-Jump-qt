#ifndef ABSTRACTOBJECTCONTROLLER_H
#define ABSTRACTOBJECTCONTROLLER_H

#include "messageheader.h"
#include "messagenegotiator.h"
#include "core_global.h"
#include "collisiondetector.h"

#include <QRectF>

enum class ControllerType
{
    SLAB,
    MONSTER,
    DOODLER,
    GHOST,      //multiplayer doodler
    BULLET,
    POWERUP
};

class EngineBase;

class CORE_EXPORT AbstractObjectController
{
public:
    AbstractObjectController();
    virtual ~AbstractObjectController();

    virtual void proceedCollision(ControllerType controllerType, CollisionType collisionType) = 0;
    virtual void proceed(double dt) = 0;
    virtual void init(QPoint startPoint) = 0;

    QRectF getBoundingRect();

    QByteArray proceedMsg(MessageHeader *header, QDataStream &stream);

    void setPiId(int value);
    int getPiId() const { return m_id; }
    void setEngineBase(EngineBase *e);
    CollisionType getCollisionType();

protected:
    EngineBase *m_engine;
    uint32_t m_id;
    MessageNegotiator *m_negotiator;

    QRectF m_boundingRect;
    CollisionType m_collisionType = CollisionType::NONE;
};

#endif // ABSTRACTCONTROLLER_H
