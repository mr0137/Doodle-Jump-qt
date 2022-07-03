#ifndef SLABHMOVINGCONTROLLER_H
#define SLABHMOVINGCONTROLLER_H

#include "slabcontroller.h"

class SlabHMovingController : public SlabController
{
public:
    SlabHMovingController();
    virtual void proceed(double dt) override;
    virtual void init(QPoint startPoint) override;

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
        VELOCITY_DOWN = 0x016,
        VELOCITY_UP = 0x032
    };
    Q_DECLARE_FLAGS(MovingModes, MovingMode)
    MovingModes mode;
};

#endif // SLABHMOVINGCONTROLLER_H
