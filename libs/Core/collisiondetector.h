#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <cstdint>
class DoodlerController;
class AbstractObjectController;

enum class CollisionType : uint8_t
{
    NONE = 0x00,
    TOP = 0x01,
    BOTTOM = 0x02,
    LEFT = 0x04,
    RIGHT = 0x08
};

//uint8_t operator&(CollisionType type1, CollisionType type2)
//{
//    return static_cast<uint8_t>(type1) &  static_cast<uint8_t>(type2);
//}
//
//uint8_t operator==(uint8_t type1, CollisionType type2)
//{
//    return static_cast<uint8_t>(type1) == static_cast<uint8_t>(type2);
//}

class CollisionDetector
{
public:
    CollisionDetector();
    void proceed(AbstractObjectController* doodlerController, AbstractObjectController *object);
};

#endif // COLLISIONDETECTOR_H
