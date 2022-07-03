#include "slabhmovingcontroller.h"
#include <messages/changecoordsmsg.h>
#include <enginebase.h>
#include <engineinterface.h>

SlabHMovingController::SlabHMovingController() : SlabController()
{

}

void SlabHMovingController::proceed(double dt)
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

        m_engine->getInterface()->sendFromEngine(msg, m_id);

    }
}

void SlabHMovingController::init(QPoint startPoint)
{
    m_boundingRect = QRectF(startPoint.x(), startPoint.y(), m_boundingRect.width(), m_boundingRect.height());
    mode = LEFT;
    mode.setFlag(VELOCITY_UP);

    m_internalVelocity = velocity;
    m_inited = true;
}
