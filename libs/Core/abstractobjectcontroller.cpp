#include "abstractobjectcontroller.h"

AbstractObjectController::AbstractObjectController()
{
    this->mDisp = new MessageNegotiator;
}

AbstractObjectController::~AbstractObjectController()
{
    delete this->mDisp;
}

void AbstractObjectController::setPiId(int value)
{
    piId = value;
}

void AbstractObjectController::setEngine(Engine *value)
{
    e = value;
}

QByteArray AbstractObjectController::proceedMsg(MessageHeader* h, QDataStream &s)
{
    return this->mDisp->proceedMsg(h, s);
}
