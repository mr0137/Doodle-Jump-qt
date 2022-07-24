#include "doodlercontroller.h"

#include <messages/changecoordsmsg.h>
#include <messages/changeviewrect.h>
#include <engineinterface.h>

DoodlerController::DoodlerController()
{
    m_boundingRect = {0,0,50,50};
    m_collidableTypes = (static_cast<int>(ControllerType::SLAB) | static_cast<int>(ControllerType::MONSTER) | static_cast<int>(ControllerType::POWERUP) | static_cast<int>(ControllerType::TRAP));
    m_controllerType = ControllerType::DOODLER;
    m_negotiator->registerMsgHandler(&DoodlerController::proceedSetVelocity, this);
}

void DoodlerController::proceedCollision(ControllerType ControllerType, CollisionType collisionType)
{
    if (ControllerType == ControllerType::SLAB && collisionType == CollisionType::BOTTOM)
    {
        m_velocityY = 3.5;
    }
}

void DoodlerController::proceed(double dt, QRectF &visualRect)
{
    bool flyMode = false;
    auto delta = m_gravity / dt;
    m_velocityY -= delta;
    if (!m_moving)
    {
        if (m_velocityX > 0 && m_velocityX - delta <= 0)
        {
            m_velocityX = 0;
        }
        else if (m_velocityX < 0 && m_velocityX + delta >= 0)
        {
            m_velocityX = 0;
        }
        else if (m_velocityX > 0)
        {
            m_velocityX -= delta;
        }
        else if (m_velocityX < 0)
        {
            m_velocityX += delta;
        }
    }

    if (!flyMode)
    {
        if (m_boundingRect.x() + m_boundingRect.width()/2 + m_velocityX >= visualRect.width())
        {
            changeX(m_boundingRect.x() + m_velocityX + m_boundingRect.width()/2 - visualRect.width());
        }
        else if (m_boundingRect.x() + m_velocityX <= visualRect.x() - m_boundingRect.width()/2)
        {
            changeX(m_boundingRect.x() + m_velocityX + visualRect.width());
        }
        else
        {
            changeX(m_boundingRect.x() + m_velocityX);
        }
        changeY(m_boundingRect.y() + m_velocityY);
    }
    else
    {
        changeY(m_boundingRect.y() - m_velocityX);
    }

    ChangeCoordsMsg msg;
    msg.x = m_boundingRect.x();
    msg.y = m_boundingRect.y();

    m_engine->getInterface()->sendFromEngine(msg, m_id);
}

void DoodlerController::init(QPointF pos)
{
    changePos(pos);
}

SetVelocityMsgAns DoodlerController::proceedSetVelocity(SetVelocityMsg msg)
{
    if (msg.velocity == 1)
    {
        m_velocityX = 1;
        m_moving = true;
    }
    else if (msg.velocity == -1)
    {
        m_velocityX = -1;
        m_moving = true;
    }
    else if (msg.velocity == -2 && m_velocityX < 0)
    {
        m_moving = false;
    }
    else if (msg.velocity == 2 && m_velocityX > 0)
    {
        m_moving = false;
    }
    //qDebug() << m_velocityX << msg.velocity;
    SetVelocityMsgAns ans;
    ans.success = true;
    return ans;
}
