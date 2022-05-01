#include "doodlercontroller.h"

DoodlerController::DoodlerController()
{
    m_boundingRect = {0,0,50,50};
}

void DoodlerController::proceedCollision(ControllerType controllerType, CollisionType collisionType)
{

}

void DoodlerController::proceed(double dt)
{

}

void DoodlerController::init(MessageBase *message, EngineBase *engine)
{

}

double DoodlerController::getVelocityY()
{
    return m_velocityY;
}

double DoodlerController::getVelocityX()
{
    return m_velocityX;
}
