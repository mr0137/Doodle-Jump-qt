#ifndef REMOVEITEMMESSAGE_H
#define REMOVEITEMMESSAGE_H

#include <imessage.h>
#include <vector>
#include <pluginsbase_global.h>
#include <QDataStream>

struct PLUGINSBASE_EXPORT RemoveItemMessage : MessageBase
{
    uint32_t getType() const override { return m_messageType; }
    static bool checkType(uint32_t type) { return type == m_messageType; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_messageType; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    std::vector<uint32_t> ids;

private:
     static inline uint32_t m_messageType = 3;
};

struct PLUGINSBASE_EXPORT RemoveItemMessageAns : MessageBase
{
    uint32_t getType() const override { return m_messageType; }
    static bool checkType(uint32_t type) { return type == m_messageType; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_messageType; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    bool modeChangedSuccess;

private:
     static inline uint32_t m_messageType = 4;
};

#endif // REMOVEITEMMESSAGE_H
