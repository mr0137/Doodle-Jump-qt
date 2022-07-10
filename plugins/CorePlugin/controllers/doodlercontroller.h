#ifndef DOODLERCONTROLLER_H
#define DOODLERCONTROLLER_H

#include "abstractobjectcontroller.h"

class DoodlerController : public AbstractObjectController
{
public:
    DoodlerController();

    virtual void proceedCollision(ControllerType controllerType, CollisionType collisionType) override;
    virtual void proceed(double dt) override;
    virtual void init(QPointF pos) override;

private:
    double m_gravity = 9.8;
};

#endif // DOODLERCONTROLLER_H
