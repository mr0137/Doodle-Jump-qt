#include "messageheader.h"
#include "engineinterface.h"
#include "messagenegotiator.h"

EngineInterface::EngineInterface(): fromEngine(200), toEngine(200)
{
    answerDispatcher = new MessageAnswerDispatcher;
}

EngineInterface::~EngineInterface()
{
    delete answerDispatcher;
}

void EngineInterface::proceed() {
    while (true) {
        auto bA = fromEngine.pop();
        if (bA.size() < 4) break; //no message to proceed
        QDataStream s(bA);
        MessageHeader h;
        s >> h;
        //proceed answer
        int pos = s.device()->pos();
        if (h.isAnswer) {
            answerDispatcher->proceedMsgAnswer(h, s);
        } else {
            auto search = msgFromEngineHandlers.find(h.type);
            if(search != msgFromEngineHandlers.end()){
                search->second(s, h.itemId);
            }
        }
        s.device()->seek(pos);
        runConnections(h.type, s);
    }
}

void EngineInterface::_pushAnswerEngineSide(const QByteArray & msg, MessageHeader * header)
{
    QByteArray data;
    QDataStream s(&data, QIODevice::ReadWrite);
    s << *header;
    data.append(msg);
    fromEngine.push(data);
}










