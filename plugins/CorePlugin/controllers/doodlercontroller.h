#ifndef DOODLERCONTROLLER_H
#define DOODLERCONTROLLER_H

#include "abstractobjectcontroller.h"

class DoodlerController : public AbstractObjectController
{
public:
    DoodlerController();

    virtual void proceedCollision(ControllerType controllerType, CollisionType collisionType) override;
    virtual void proceed(double dt) override;
    virtual void init(QPoint pos) override;
    double getVelocityY();
    double getVelocityX();
private:
    double m_velocityX = 0;
    double m_velocityY = 0;
};

#endif // DOODLERCONTROLLER_H
