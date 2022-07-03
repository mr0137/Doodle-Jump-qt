#ifndef SLABVMOVINGCONTROLLER_H
#define SLABVMOVINGCONTROLLER_H

#include "slabcontroller.h"

class SlabVMovingController : public SlabController
{
public:
    SlabVMovingController();
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
        UP = 0x04,
        DOWN = 0x08,
        VELOCITY_DOWN = 0x016,
        VELOCITY_UP = 0x032
    };
    Q_DECLARE_FLAGS(MovingModes, MovingMode)
    MovingModes mode;
};

#endif // SLABVMOVINGCONTROLLER_H
