#ifndef EMPTYMESSAGE_H
#define EMPTYMESSAGE_H

#include <core_global.h>
#include "messagebase.h"

struct CORE_EXPORT EmptyMessage : public MessageBase
{
    EmptyMessage() {}
    int getType() const override {return m_type;}
    static bool checkType(int type) {return type == m_type;}
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
private:
    inline static int m_type = 0;
public:

    void serialize(QDataStream *) const override {};
    void deserialize(QDataStream *) override {};
};
#endif // EMPTYMESSAGE_H
