#include "abstractobjectcontroller.h"

AbstractObjectController::AbstractObjectController()
{
    m_negotiator = new MessageNegotiator;
}

AbstractObjectController::~AbstractObjectController()
{
    delete m_negotiator;
}

QRectF AbstractObjectController::getBoundingRect()
{
    return m_boundingRect;
}

void AbstractObjectController::setPiId(int value)
{
    m_id = value;
}

void AbstractObjectController::setEngineBase(EngineBase *value)
{
    m_engine = value;
}

CollisionType AbstractObjectController::getCollisionType()
{
    return m_collisionType;
}

QByteArray AbstractObjectController::proceedMsg(MessageHeader* header, QDataStream &stream)
{
    return m_negotiator->proceedMsg(header, stream);
}
