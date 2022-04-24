#ifndef ENGINEBASE_H
#define ENGINEBASE_H

#include <vector>
#include <map>
#include <functional>
#include "abstractobjectcontroller.h"
#include <messagenegotiator.h>
#include <engineinterface.h>
#include <core_global.h>
#include <mutex>

class AbstractObjectController;
class EngineInterface;

class CORE_EXPORT EngineBase
{
public:
    EngineBase();
    ~EngineBase();

    EngineInterface *getInterface() const;

    virtual void start() = 0;
    virtual void stop() = 0;

    int lastCreatedPIID;

    unsigned long long engineTime() const;
    std::vector<std::function<void()>> oneSecondCallbacks;

    std::map<int, AbstractObjectController *> & getPiControllers();

protected:
    void proceed(int uSecond, int dt);
    bool removeController(int id);
    void insertController(int id, AbstractObjectController *c);
    QByteArray proceedItemMsg(MessageHeader header, QDataStream &s);

    std::map<int, AbstractObjectController*> m_objectControllers;
    MessageNegotiator *messageNegotiator;
    EngineInterface *m_interface;
    bool doMath;

private:
    int prevTime_us = 0;
    unsigned long long m_engineTime = 0;
};


#endif // ENGINEBASE_H
