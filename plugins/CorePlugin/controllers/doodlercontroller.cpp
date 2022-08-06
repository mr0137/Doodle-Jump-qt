#include "doodlercontroller.h"

#include <messages/changecoordsmsg.h>
#include <messages/changeviewrect.h>
#include <engineinterface.h>


DoodlerController::DoodlerController() : AbstractObjectController()
{
    m_boundingRect = {0,0,50,50};
    m_collidableTypes = (static_cast<int>(ControllerType::SLAB) | static_cast<int>(ControllerType::MONSTER) | static_cast<int>(ControllerType::POWERUP) | static_cast<int>(ControllerType::TRAP));
    m_controllerType = ControllerType::DOODLER;
    m_negotiator->registerMsgHandler(&DoodlerController::proceedSetVelocity, this);
    m_easing = new QEasingCurve(QEasingCurve::Type::OutSine);
}

void DoodlerController::proceedCollision(ControllerType ControllerType, CollisionType collisionType)
{
    if (ControllerType == ControllerType::SLAB && collisionType == CollisionType::BOTTOM)
    {
        m_jumping = true;
        m_velocityY = 3.2;
    }
}

void DoodlerController::proceed(double dt, QRectF &visualRect)
{
    bool flyMode = false;
    static int i = 0;
    //qDebug() << m_delta * m_velocityMult;
    //! [block Y]
    //if (m_jumping)
    //{
    //    m_velocityY = 0;
    //    m_jumping = false;
    //    m_easingProgress = 0;
    //    m_yBeforeJump = m_boundingRect.y();
    //}

    //if (m_easingProgress < 1)
    //{
    //    double coef = m_easing->valueForProgress(m_easingProgress);
    //    changeY(m_yBeforeJump + m_jumpHeight * coef);
    //    m_easingProgress+= dt/1000000. * 3;
    //}
    //else
    //{
    //    m_velocityY -= m_delta * 1.5;
    //    changeY(m_boundingRect.y() + m_velocityY);
    //}
    ////! [block Y]
    ///
    ///
    if (m_velocityY == 3.2)
    {
       // qDebug() << m_boundingRect.y() << 0;
        i = 0;
    }
    i++;
    if (m_velocityY <= 0)
    {
       // qDebug() << m_boundingRect.y() << i;
        i = 0;
    }
    m_velocityY -= m_delta * dt;

    changeY(m_boundingRect.y() + m_velocityY);


    if (!m_moving)
    {
        if (m_velocityX > 0 && m_velocityX - m_delta*dt <= 0)
        {
            m_velocityX = 0;
        }
        else if (m_velocityX < 0 && m_velocityX + m_delta*dt >= 0)
        {
            m_velocityX = 0;
        }
        else if (m_velocityX > 0)
        {
            m_velocityX -= m_delta*dt;
        }
        else if (m_velocityX < 0)
        {
            m_velocityX += m_delta*dt;
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

/*
 *     bool flyMode = false;
    qDebug() << m_delta * m_velocityMult;

    if (m_jumping)
    {
        m_velocityY = 0;
        m_jumping = false;
        m_easingProgress = 0;
        m_yBeforeJump = m_boundingRect.y();
    }

    if (m_easingProgress < 1)
    {
        double coef = m_easing->valueForProgress(m_easingProgress);
        changeY(m_yBeforeJump + m_jumpHeight * coef);
        m_easingProgress+= dt/1000000.;
    }
    else
    {
        m_velocityY -= m_delta*1.5;
        changeY(m_boundingRect.y() + m_velocityY);
    }

    if (!m_moving)
    {
        if (m_velocityX > 0 && m_velocityX - m_delta * m_velocityMult <= 0)
        {
            m_velocityX = 0;
        }
        else if (m_velocityX < 0 && m_velocityX + m_delta * m_velocityMult >= 0)
        {
            m_velocityX = 0;
        }
        else if (m_velocityX > 0)
        {
            m_velocityX -= m_delta * m_velocityMult;
        }
        else if (m_velocityX < 0)
        {
            m_velocityX += m_delta * m_velocityMult;
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
        //changeY(m_boundingRect.y() + m_velocityY);
    }
    else
    {
        changeY(m_boundingRect.y() - m_velocityX);
    }

    ChangeCoordsMsg msg;
    msg.x = m_boundingRect.x();
    msg.y = m_boundingRect.y();

    m_engine->getInterface()->sendFromEngine(msg, m_id);
    */
