#include "collisiondetector.h"
#include "abstractobjectcontroller.h"

CollisionDetector::CollisionDetector()
{

}

void CollisionDetector::proceed(AbstractObjectController *targetController, AbstractObjectController *object)
{
    if (targetController->getVelocityY() < 0)
    {
        QRectF doodlerRect = targetController->getBoundingRect();
        QRectF objectRect = object->getBoundingRect();
        if (doodlerRect.intersects(objectRect))
        {
            if (doodlerRect.x() <= objectRect.x() + objectRect.width() && doodlerRect.x() + doodlerRect.width() >= objectRect.x())
            {
                if (doodlerRect.y() + doodlerRect.height() >= objectRect.y() + objectRect.height() / 2)
                {
                    targetController->proceedCollision(object->getControllerType(), CollisionType::BOTTOM);
                }
            }
        }
    }
}
