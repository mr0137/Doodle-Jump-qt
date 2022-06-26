#ifndef ENGINEBASE_H
#define ENGINEBASE_H

#include <vector>
#include <map>
#include <functional>
#include "abstractobjectcontroller.h"
#include "levelgenerator.h"
#include <messagenegotiator.h>
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
    LevelGenerator *getLevelGenerator() const;

    virtual void start() = 0;
    virtual void stop() = 0;

    unsigned long long engineTime() const;
    std::vector<std::function<void()>> oneSecondCallbacks;

    const std::map<uint32_t, AbstractObjectController *> *getPiControllers();

protected:
    void proceed(int uSecond, int dt);
    bool removeController(uint32_t id);
    void insertController(uint32_t id, AbstractObjectController *c);
    QByteArray proceedItemMsg(MessageHeader header, QDataStream &s);

protected:
    uint32_t m_lastCreatedPIID = 0;
    std::map<uint32_t, AbstractObjectController*> m_objectControllers;
    std::map<uint32_t, AbstractObjectController*> m_collideObjectControllers;
    MessageNegotiator *messageNegotiator;
    EngineInterface *m_interface;
    LevelGenerator *m_levelGenerator;
    CollisionDetector *m_collisionDetector;
    bool doMath = false;

private:
    int prevTime_us = 0;
    unsigned long long m_engineTime = 0;
};


#endif // ENGINEBASE_H
