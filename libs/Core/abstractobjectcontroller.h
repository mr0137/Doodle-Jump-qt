#ifndef ABSTRACTOBJECTCONTROLLER_H
#define ABSTRACTOBJECTCONTROLLER_H

#include "messageheader.h"
#include "messagenegotiator.h"
#include "core_global.h"
#include "collisiondetector.h"

enum class ControllerType
{
    SLAB,
    MONSTER,
    DOODLER,
    GHOST
};

struct Rect
{
    Rect(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    void changePos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(Rect& rect)
    {
        return this->x == rect.x &&
                this->y == rect.y &&
                this->width == rect.width &&
                this->height == rect.height;
    }

    int x;
    int y;
    int width;
    int height;
};

class EngineBase;

class CORE_EXPORT AbstractObjectController
{
public:
    AbstractObjectController();
    virtual ~AbstractObjectController();

    virtual void proceedCollision(ControllerType controllerType, CollisionType collisionType) = 0;
    virtual void proceed(double dt) = 0;
    virtual void init(MessageBase * message, EngineBase *engine) = 0;

    Rect getBoundingRect();

    QByteArray proceedMsg(MessageHeader *header, QDataStream &stream);

    void setPiId(int value);
    int getPiId() const { return m_id; }
    void setEngineBase(EngineBase *e);
    CollisionType getCollisionType();

protected:
    EngineBase *m_engine;
    int m_id;
    MessageNegotiator *m_negotiator;

    Rect m_boundingRect = {0,0,0,0};
    CollisionType m_collisionType = CollisionType::NONE;
};

#endif // ABSTRACTCONTROLLER_H
