#ifndef CREATEITEMMESSAGE_H
#define CREATEITEMMESSAGE_H

#include <imessage.h>
#include <pluginsbase_global.h>
#include <QDataStream>
#include <QString>

struct PLUGINSBASE_EXPORT CreateItemMsg : MessageBase
{
    uint32_t getType() const override { return m_type; }
    static bool checkType(uint32_t type) { return type == m_type; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_type; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    double x;
    double y;
    uint32_t id;
    QString objectType;

private:
    static inline uint32_t m_type = 1;
};

struct PLUGINSBASE_EXPORT CreateItemMsgAns : MessageBase
{
    uint32_t getType() const override { return m_messageType; }
    static bool checkType(uint32_t type) { return type == m_messageType; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_messageType; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    uint32_t id;
    QString objectType;

private:
     static inline uint32_t m_messageType = 2;
};

#endif // CREATEITEMMESSAGE_H
