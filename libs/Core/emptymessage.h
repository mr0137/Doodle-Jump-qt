#ifndef EMPTYMESSAGE_H
#define EMPTYMESSAGE_H

#include <core_global.h>
#include "imessage.h"

struct CORE_EXPORT EmptyMessage : public MessageBase
{
    uint32_t getType() const override { return m_type; }
    static bool checkType(uint32_t type) { return type == m_type; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_type; }
    void serialize(QDataStream *) const override {}
    void deserialize(QDataStream *) override {}

private:
    static inline uint32_t m_type = 0;
};
#endif // EMPTYMESSAGE_H
