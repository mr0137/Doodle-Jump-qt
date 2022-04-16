#ifndef IMESSSAGE_H
#define IMESSSAGE_H

#include <QDataStream>

struct IMessage
{
    IMessage() = default;
    virtual ~IMessage();

    virtual int getType() const = 0;
    virtual void serialize(QDataStream *s) const = 0;
    virtual void deserialize(QDataStream *s) = 0;
};

#endif // IMESSSAGE_H
