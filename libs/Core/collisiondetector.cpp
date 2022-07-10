#include "collisiondetector.h"
#include "abstractobjectcontroller.h"

CollisionDetector::CollisionDetector()
{

}

void CollisionDetector::proceed(AbstractObjectController *doodlerController, AbstractObjectController *object)
{
    if (doodlerController->getVelocityY() < 0)
    {
        QRectF doodlerRect = doodlerController->getBoundingRect();
        QRectF objectRect = object->getBoundingRect();
        if (doodlerRect.intersects(objectRect))
        {
            if (doodlerRect.x() <= objectRect.x() + objectRect.width() && doodlerRect.x() + doodlerRect.width() >= objectRect.x())
            {
                if (doodlerRect.y() + doodlerRect.height() >= objectRect.y() + objectRect.height() / 2)
                {
                    doodlerController->proceedCollision(object->getControllerType(), CollisionType::BOTTOM);
                }
            }
        }
    }
}
