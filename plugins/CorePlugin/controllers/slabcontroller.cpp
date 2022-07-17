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

void SlabController::proceed(double dt, const QRectF &visualRect)
{

}

void SlabController::init(QPointF pos)
{
    changePos(pos);
}
