#include "collisiondetector.h"
#include "abstractobjectcontroller.h"

CollisionDetector::CollisionDetector()
{

}

void CollisionDetector::proceed(AbstractObjectController *doodlerController, AbstractObjectController *object)
{
    //auto doodler = static_cast<DoodlerController*>(doodlerController);
    //if (!doodler)
    //{
    //     return;
    //}


    //if (doodler->getVelocityY() < 0 &&
    //        (static_cast<uint8_t>(object->getCollisionType()) & static_cast<uint8_t>(CollisionType::TOP)) == static_cast<uint8_t>(CollisionType::TOP))
    //{

    //}
}
