#ifndef SLABVMOVINGCONTROLLER_H
#define SLABVMOVINGCONTROLLER_H

#include "slabcontroller.h"

class SlabVMovingController : public SlabController
{
public:
    SlabVMovingController();
    virtual void proceed(double dt, const QRectF & visualRect) override;
    virtual void init(QPointF startPoint) override;

private:
    bool m_inited = false;
    qreal top = 100;
    qreal bottom = 1200;
    qreal speed = 1.5;
    qreal velocity = 50;
    qreal m_internalVelocity;
    enum MovingMode{
        NONE = 0x00,
        UP = 0x01,
        DOWN = 0x02,
        VELOCITY_DOWN = 0x04,
        VELOCITY_UP = 0x08
    };
    Q_DECLARE_FLAGS(MovingModes, MovingMode)
    MovingModes mode;
};

#endif // SLABVMOVINGCONTROLLER_H
