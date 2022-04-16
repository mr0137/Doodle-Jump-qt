#ifndef ABSTRACTOBJECTCONTROLLER_H
#define ABSTRACTOBJECTCONTROLLER_H

#include "messageheader.h"
#include "messagenegotiator.h"
#include "core_global.h"

class Engine;

class CORE_EXPORT AbstractObjectController
{
public:
    AbstractObjectController();
    virtual ~AbstractObjectController();

    virtual void proceed(double) = 0;
    virtual void init(MessageBase * msg, Engine * e) = 0;

    QByteArray proceedMsg(MessageHeader *h, QDataStream &s);

    void setPiId(int value);
    int getPiId() const { return piId; }
    void setEngine(Engine *e);

protected:
    Engine *e;
    int piId;
    MessageNegotiator * mDisp;
};

#endif // ABSTRACTCONTROLLER_H
