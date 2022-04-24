#include "enginebase.h"

EngineBase::EngineBase()
{
    m_interface = new EngineInterface;
    m_interface->m_engine = this;
    messageNegotiator = new MessageNegotiator;

    doMath = false;
}

EngineBase::~EngineBase()
{
    delete m_interface;
    delete messageNegotiator;
}

EngineInterface *EngineBase::getInterface() const
{
    return m_interface;
}

void EngineBase::proceed(int uSecond, int dt)
{
    Q_UNUSED(dt)
    //take msgs from interface and proceed them
    while (true) {
        QByteArray serMsg = m_interface->toEngineBase.pop();
        if (serMsg.isEmpty()) break;
        QDataStream stream(&serMsg, QIODevice::ReadOnly);
        MessageHeader msgMessageHeader;
        stream >> msgMessageHeader;

        QByteArray answ;
        if (msgMessageHeader.itemId == -1) { //msg for controller
            answ = messageNegotiator->proceedMsg(&msgMessageHeader, stream);

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

void EngineBase::insertController(int id, AbstractObjectController * c)
{
    m_objectControllers.insert({id, c});
}

bool EngineBase::removeController(int id)
{
    AbstractObjectController * p = m_objectControllers[id];
    delete p;
    m_objectControllers.erase(id);
    return true;
}

QByteArray EngineBase::proceedItemMsg(MessageHeader header, QDataStream &s)
{
    for (auto c : m_objectControllers) {
        if (c.second->getPiId() == header.itemId) {
            return c.second->proceedMsg(&header, s);
        }
    }
    return nullptr;
}

std::map<int, AbstractObjectController *> & EngineBase::getPiControllers()
{
    return m_objectControllers;
}

unsigned long long EngineBase::engineTime() const
{
    return m_engineTime;
}
