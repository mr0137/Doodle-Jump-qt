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
    virtual void init(MessageBase * message, Engine * engine) = 0;

    QByteArray proceedMsg(MessageHeader *header, QDataStream &stream);

    void setPiId(int value);
    int getPiId() const { return m_id; }
    void setEngine(Engine *e);

protected:
    Engine *m_engine;
    int m_id;
    MessageNegotiator *m_negotiator;
};

#endif // ABSTRACTCONTROLLER_H
