#include "messageheader.h"
#include "engineinterface.h"
#include "messagenegotiator.h"

EngineInterface::EngineInterface(): fromEngineBase(46000), toEngineBase(46000)
{
    answerDispatcher = new MessageAnswerDispatcher;
}

EngineInterface::~EngineInterface()
{
    delete answerDispatcher;
}

void EngineInterface::proceed()
{
    try
    {
        while (true)
        {
            auto bA = fromEngineBase.pop();
            if (bA.size() < 4) break; //no message to proceed
            QDataStream s(bA);
            MessageHeader h;
            s >> h;
            //proceed answer
            int pos = s.device()->pos();
            if (h.isAnswer)
            {
                answerDispatcher->proceedMsgAnswer(h, s);
            }
            else
            {
                auto search = msgFromEngineBaseHandlers.find(h.type);
                if(search != msgFromEngineBaseHandlers.end())
                {
                    search->second(s, h.itemId);
                }
            }
            s.device()->seek(pos);
            runConnections(h.type, s);
        }
    }
    catch(const std::exception& ex)
    {
        qCritical() << "EngineInterface::proceed failed. Error:" << ex.what();
    }
}

void EngineInterface::_pushAnswerEngineSide(const QByteArray & msg, MessageHeader * header)
{
    QByteArray data;
    QDataStream s(&data, QIODevice::ReadWrite);
    s << *header;
    data.append(msg);
    fromEngineBase.push(data);
}
