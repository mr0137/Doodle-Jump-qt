#include "slabvmovingcontroller.h"
#include <messages/changecoordsmsg.h>
#include <enginebase.h>
#include <engineinterface.h>

SlabVMovingController::SlabVMovingController() : SlabController()
{

}

void SlabVMovingController::proceed(double dt, const QRectF &visualRect)
{
    if (m_inited)
    {
        if (mode.testFlag(DOWN))
        {
            auto step = (m_internalVelocity * dt/100000) * speed;
            changeY(m_boundingRect.y() - step);
            if (top > m_boundingRect.y() - step)
            {
                mode = VELOCITY_DOWN;
                mode.setFlag(DOWN);
            }
            if (m_internalVelocity <= 0)
            {
                m_internalVelocity = 0;
                mode = VELOCITY_UP;
                mode.setFlag(UP, true);
                //mode.setFlag(LEFT, false);
            }
        }
        else if (mode.testFlag(UP))
        {
            auto step = (m_internalVelocity * dt/100000) * speed;
            changeY(m_boundingRect.y() + step);
            if (bottom < m_boundingRect.y() + step)
            {
                mode = VELOCITY_DOWN;
                mode.setFlag(UP);
            }

            if (m_internalVelocity <= 0)
            {
                m_internalVelocity = 0;
                mode = VELOCITY_UP;
                mode.setFlag(DOWN, true);
                //mode.setFlag(RIGHT, false);
            }
        }

        if (mode.testFlag(VELOCITY_DOWN))
        {
            if (m_internalVelocity > 0)
            {
                m_internalVelocity -= dt/100000 * velocity;
            }
        }
        else if (mode.testFlag(VELOCITY_UP))
        {
            if (m_internalVelocity < velocity)
            {
               m_internalVelocity += dt/100000 * velocity;
            }
        }

        ChangeCoordsMsg msg;
        msg.x = m_boundingRect.x();
        msg.y = m_boundingRect.y();
        //qDebug() << mode << m_internalVelocity;

        m_engine->getInterface()->sendFromEngine(msg, m_id);
    }
}

void SlabVMovingController::init(QPointF startPoint)
{
    m_boundingRect = QRectF(startPoint.x(), startPoint.y(), m_boundingRect.width(), m_boundingRect.height());
    mode = UP;
    mode.setFlag(VELOCITY_UP);

    m_internalVelocity = velocity;
    m_inited = true;
}
