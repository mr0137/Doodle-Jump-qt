#include "engine.h"

//std::mutex Engine::m;

Engine::Engine()
{
    m_interface = new EngineInterface;
    m_interface->m_engine = this;
    messageDispatcher = new MessageNegotiator;

    doMath = false;
}

Engine::~Engine()
{
    delete m_interface;
    delete messageDispatcher;
}

EngineInterface *Engine::getInterface() const
{
    return m_interface;
}

void Engine::proceed(int uSecond, int dt)
{
    Q_UNUSED(dt)
    //take msgs from interface and proceed them
    while (true) {
        QByteArray serMsg = m_interface->toEngine.pop();
        if (serMsg.isEmpty()) break;
        QDataStream stream(&serMsg, QIODevice::ReadOnly);
        MessageHeader msgMessageHeader;
        stream >> msgMessageHeader;

        QByteArray answ;
        if (msgMessageHeader.itemId == -1) { //msg for controller
            answ = messageDispatcher->proceedMsg(&msgMessageHeader, stream);

        } else { //global msg
            answ = proceedItemMsg(msgMessageHeader, stream);
        }
        if (answ.size() > 0) {
            m_interface->_pushAnswerEngineSide(answ, &msgMessageHeader);
        }
    }
    if(doMath){
        //proceed physical items
        for (auto c : m_objectControllers) {
            c.second->proceed(1000);
        }
        if(!(m_engineTime % 1000000))
            for(auto && fn : oneSecondCallbacks)
                fn();

        m_engineTime += 1000; // uSecond
        prevTime_us = uSecond;
    }


}

void Engine::insertController(int id, AbstractObjectController * c)
{
    m_objectControllers.insert({id, c});
}

bool Engine::removeController(int id)
{
    AbstractObjectController * p = m_objectControllers[id];
    delete p;
    m_objectControllers.erase(id);
    return true;
}

QByteArray Engine::proceedItemMsg(MessageHeader header, QDataStream &s)
{
    for (auto c : m_objectControllers) {
        if (c.second->getPiId() == header.itemId) {
            return c.second->proceedMsg(&header, s);
        }
    }
    return nullptr;
}

std::map<int, AbstractObjectController *> & Engine::getPiControllers()
{
    return m_objectControllers;
}

unsigned long long Engine::engineTime() const
{
    return m_engineTime;
}
