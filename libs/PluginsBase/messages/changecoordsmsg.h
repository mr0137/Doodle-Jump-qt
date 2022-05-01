#ifndef CHANGECOORDSMSG_H
#define CHANGECOORDSMSG_H

#include <imessage.h>
#include <pluginsbase_global.h>

struct PLUGINSBASE_EXPORT ChangeCoordsMsg : MessageBase
{
    uint32_t getType() const override { return m_messageType; }
    static bool checkType(uint32_t type) { return type == m_messageType; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_messageType; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    double x;
    double y;
    uint32_t id;

private:
    const static uint32_t m_messageType = 7;
};

struct PLUGINSBASE_EXPORT ChangeCoordsMsgAns : MessageBase
{
    uint32_t getType() const override { return m_messageType; }
    static bool checkType(uint32_t type) { return type == m_messageType; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_messageType; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    bool success;
    int id;

private:
    const static uint32_t m_messageType = 8;
};

#endif // CHANGECOORDSMSG_H
