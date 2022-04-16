#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include "core_global.h"

struct CORE_EXPORT MessageBase
{
    MessageBase() {}
    MessageBase(const MessageBase&) {}
    virtual ~MessageBase() {}
    virtual int getType() const = 0;
    virtual void serialize(QDataStream *s) const = 0;
    virtual void deserialize(QDataStream *s) = 0;
};

#endif // MESSAGEBASE_H
