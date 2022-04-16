#ifndef MESSAGENEGOTIATOR_H
#define MESSAGENEGOTIATOR_H

#include <QDataStream>
#include <map>
#include "messageheader.h"
#include "emptymessage.h"
#include "core_global.h"

class CORE_EXPORT MessageNegotiator
{
public:
    MessageNegotiator();
    template<class TMsg, class TClass, class TAns>
    //!
    //! \brief Registers handler to particular message
    //! \param obj
    //!
    void registerMsgHandler(TAns (TClass::*m)(TMsg), TClass *obj){
        int type = TMsg().getType();

        auto funcTobeCalled = [=](MessageHeader* h, QDataStream &s)->QByteArray {
            //call handler
            TMsg msg;
            msg.deserialize(&s);
            TAns answ = (obj->*m)(msg);
            if (EmptyMessage::checkType(answ.getType())) {
                return {};
            }
            //has answer
            h->type = answ.getType();
            h->isAnswer = true;
            QByteArray arr;
            QDataStream answerSerialize(&arr, QIODevice::ReadWrite);
            answ.serialize(&answerSerialize);
            return arr;
        };
        msgHandlers.insert({type, funcTobeCalled});
    }

    //!
    //! \brief Executes callback when it is found in registered callbacks
    //! \param h
    //! \param s
    //! \return QByteArray with answer
    //!
    QByteArray proceedMsg(MessageHeader* h, QDataStream &s){
        auto found = msgHandlers.find(h->type);
            if(found != msgHandlers.end()){
                return found->second(h, s);
            }
        return nullptr;
    }

private:
    std::map<int, std::function<QByteArray(MessageHeader*, QDataStream &s)>> msgHandlers;
};

#endif // MESSAGENEGOTIATOR_H
