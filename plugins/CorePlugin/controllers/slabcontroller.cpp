#include "slabcontroller.h"

SlabController::SlabController()
{
    m_boundingRect = {0, 0, 100, 30};
}

void SlabController::proceedCollision(ControllerType controllerType, CollisionType collisionType)
{

}

void SlabController::proceed(double dt)
{

}

void SlabController::init(QPoint pos)
{
    m_boundingRect.setTopLeft(pos);
}
