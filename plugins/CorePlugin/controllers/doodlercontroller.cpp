#include "doodlercontroller.h"

#include <messages/changecoordsmsg.h>
#include <engineinterface.h>

DoodlerController::DoodlerController()
{
    m_boundingRect = {0,0,50,50};
    m_collidableTypes = (static_cast<int>(ControllerType::SLAB) | static_cast<int>(ControllerType::MONSTER) | static_cast<int>(ControllerType::POWERUP) | static_cast<int>(ControllerType::TRAP));
    m_controllerType = ControllerType::DOODLER;
}

void DoodlerController::proceedCollision(ControllerType ControllerType, CollisionType collisionType)
{
    if (ControllerType == ControllerType::SLAB && collisionType == CollisionType::BOTTOM)
    {
        m_velocityY = 3.5;
    }
}

void DoodlerController::proceed(double dt)
{
    m_velocityY -= m_gravity / dt;
    changeY(m_boundingRect.y() - m_velocityY);

    ChangeCoordsMsg msg;
    msg.id = m_id;
    msg.x = m_boundingRect.x();
    msg.y = m_boundingRect.y();

    m_engine->getInterface()->sendFromEngine(msg, m_id);
}

void DoodlerController::init(QPointF pos)
{
    changePos(pos);
}
