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
};

#endif // SLABCONTROLLER_H
