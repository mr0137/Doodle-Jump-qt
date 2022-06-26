#ifndef SLABCONTROLLER_H
#define SLABCONTROLLER_H

#include "abstractobjectcontroller.h"

class SlabController : public AbstractObjectController
{
public:
    SlabController();
    virtual void proceedCollision(ControllerType controllerType, CollisionType collisionType) override;
    virtual void proceed(double dt) override;
    virtual void init(QPoint pos) override;
private:
    bool m_inited = false;
    qreal left;
    qreal right;
    qreal speed = 5.0;
    qreal velocity = 15;
    qreal m_internalVelocity;
    enum MovingMode{
        NONE = 0x00,
        LEFT = 0x01,
        RIGHT = 0x02,
        UP = 0x04,
        DOWN = 0x08,
        VELOCITY_DOWN = 0x016,
        VELOCITY_UP = 0x032
    };
    Q_DECLARE_FLAGS(MovingModes, MovingMode)
    MovingModes mode;

};

#endif // SLABCONTROLLER_H
