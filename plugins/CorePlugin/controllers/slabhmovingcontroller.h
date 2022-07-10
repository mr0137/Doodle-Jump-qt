#ifndef SLABHMOVINGCONTROLLER_H
#define SLABHMOVINGCONTROLLER_H

#include "slabcontroller.h"

class SlabHMovingController : public SlabController
{
public:
    SlabHMovingController();
    virtual void proceed(double dt) override;
    virtual void init(QPointF startPoint) override;

private:
    bool m_inited = false;
    qreal left = 100;
    qreal right = 600;
    qreal speed = 0.5;
    qreal velocity = 50;
    qreal m_internalVelocity;
    enum MovingMode{
        NONE = 0x00,
        LEFT = 0x01,
        RIGHT = 0x02,
        VELOCITY_DOWN = 0x04,
        VELOCITY_UP = 0x08
    };
    Q_DECLARE_FLAGS(MovingModes, MovingMode)
    MovingModes mode;
};

#endif // SLABHMOVINGCONTROLLER_H
