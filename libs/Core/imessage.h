#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QDataStream>

struct MessageBase
{
    MessageBase() = default;
    virtual ~MessageBase() {}

    virtual uint32_t getType() const = 0;
    virtual void serialize(QDataStream *s) const = 0;
    virtual void deserialize(QDataStream *s) = 0;
};

#endif // IMESSAGE_H
