#include "slabcontroller.h"

#include <messages/changecoordsmsg.h>
#include <enginebase.h>
#include <engineinterface.h>

SlabController::SlabController()
{
    m_boundingRect = {0, 0, 100, 30};
}

void SlabController::proceedCollision(ControllerType controllerType, CollisionType collisionType)
{

}

void SlabController::proceed(double dt)
{
    if (m_inited)
    {
        if (mode.testFlag(LEFT))
        {
            auto step = (m_internalVelocity * dt/100000) * speed;
            m_boundingRect.setLeft(m_boundingRect.x() - step);
            if (100 > m_boundingRect.x() - step)
            {
                mode.setFlag(VELOCITY_DOWN);
            }
            if (m_internalVelocity <= 0)
            {
                mode = VELOCITY_UP;
                mode.setFlag(RIGHT, true);
                //mode.setFlag(LEFT, false);
            }
        }
        else if (mode.testFlag(RIGHT))
        {
            auto step = (m_internalVelocity * dt/100000) * speed;
            m_boundingRect.setLeft(m_boundingRect.x() + step);
            if (500 < m_boundingRect.x() + step)
            {
                mode.setFlag(VELOCITY_DOWN);
            }

            if (m_internalVelocity <= 0)
            {
                mode = VELOCITY_UP;
                mode.setFlag(LEFT, true);
                //mode.setFlag(RIGHT, false);
            }
        }

        if (mode.testFlag(VELOCITY_DOWN))
        {
            if (m_internalVelocity > 0)
            {
                m_internalVelocity -= dt/100000 * speed;
            }
        }
        else if (mode.testFlag(VELOCITY_UP))
        {
            if (m_internalVelocity < velocity)
            {
                m_internalVelocity += dt/100000 * speed;
            }
        }

        ChangeCoordsMsg msg;
        msg.id = m_id;
        msg.x = m_boundingRect.x();
        msg.y = m_boundingRect.y();
        //qDebug() << mode << m_internalVelocity;

        m_engine->getInterface()->sendFromEngine(msg, m_id);
    }
}

void SlabController::init(QPoint pos)
{
    m_boundingRect.setTopLeft(pos);
    mode = LEFT;
    mode.setFlag(VELOCITY_UP);

    m_internalVelocity = velocity;
    m_inited = true;
}
