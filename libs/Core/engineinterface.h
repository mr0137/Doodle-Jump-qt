#ifndef ENGINEINTERFACE_H
#define ENGINEINTERFACE_H

#include "core_global.h"
#include <circlebuffer.h>
#include <engine.h>
#include <messageanswerdispatcher.h>
#include <QDataStream>
#include <map>


struct MessageBase;
class MessageNegotiator;
class Engine;
class SampleDataGetter;

class CORE_EXPORT MessageConnector {
    std::function<void(QDataStream &)> callbackOnMsg;
    int messageType;
public:

    int getMessageType() {return messageType;}

    template <typename Msg, typename Callable>
    void connectToMsg(Callable m)
    {
        messageType = Msg().getType();
        callbackOnMsg = [m](QDataStream & s){
            Msg msg;
            msg.deserialize(&s);
            m(msg);
        };
    }

    void operator()(QDataStream &s) {
        callbackOnMsg(s);
    }
};


class CORE_EXPORT EngineInterface
{
    friend class Engine;
    friend MsgAnswerHandler;
    friend class SampleDataGetter;
public:
    EngineInterface();
    ~EngineInterface();

    void proceed();

    template<class Msg>
    MsgAnswerHandler sendToEngine(Msg msg, int itemId = -1);

    template<class Msg>
    void installStreamMsg(std::function<void(Msg, int)>);

    template<class Msg, class ... Msgs>
    void sendFromEngine(Msg msg, Msgs ... msgs, int itemId = -1);

    void _pushAnswerEngineSide(const QByteArray &msg, MessageHeader *header);

    template<typename Msg, typename Callable>
    void addConnection(Callable f) {

        int type = Msg().getType();

        MessageConnector mConn;
        mConn.connectToMsg<Msg>(f);

        msgConnections[type].push_back(mConn);

    }

    void runConnections(int type, QDataStream &s) {
        if(msgConnections.find(type) != msgConnections.end()) {
            int pos = s.device()->pos();
            for(auto mConn : msgConnections[type]) {
                mConn(s);
                s.device()->seek(pos);
            }
        }
    }

private:
    CircleBuffer<QByteArray> fromEngine;
    CircleBuffer<QByteArray> toEngine;

    int nextMsgId=0;
    int nextMsgIdEngineSide=0;


    MessageAnswerDispatcher * answerDispatcher;
    Engine *m_engine;

    std::map<int, std::function<int(QDataStream &s, int)>> msgFromEngineHandlers;
    //
    std::map<int, std::vector<MessageConnector>> msgConnections;

};



template<class Msg, class ... Msgs>
void EngineInterface::sendFromEngine(Msg msg, Msgs ... msgs, int itemId)
{
    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);
    //write header
    MessageHeader header;
    header.uid = this->nextMsgIdEngineSide++;
//    qDebug() << Msg().getType();
    header.type = Msg().getType();
    header.itemId = itemId;
    header.isAnswer = false;
    s << header;
    //write msg
    msg.serialize(&s);
    fromEngine.push(data);
    if constexpr (sizeof...(msgs) > 0) {
        sendFromEngine(msgs..., itemId);
    }
}

template <class Msg>
MsgAnswerHandler EngineInterface::sendToEngine(Msg msg, int itemId)
{
    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);
    //write header
    MessageHeader header;
    header.uid = this->nextMsgId++;
    header.type = msg.getType();
    header.itemId = itemId;
    header.isAnswer = false;
    s << header;
    //write msg
    msg.serialize(&s);
    toEngine.push(data);
    MsgAnswerHandler handler(this->answerDispatcher, header.uid);
    return handler;
}

template<class Msg>
void EngineInterface::installStreamMsg(std::function<void(Msg, int)> lambda){

    auto type = Msg().getType();

    auto funcTobeCalled = [lambda](QDataStream &s, int itemId) {
        //call handler
        Msg msg;
        msg.deserialize(&s);
        lambda(msg, itemId);
        return msg.getType();
    };
    msgFromEngineHandlers.insert({type, funcTobeCalled});
}

#endif // ENGINEINTERFACE_H
