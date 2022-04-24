#ifndef STARTENGINEMSG_H
#define STARTENGINEMSG_H

#include <imessage.h>
#include <core_global.h>
#include <QDataStream>

enum EngineMode {
    START, PAUSE, RESET
};

struct CORE_EXPORT SetModeEngineMsg : public MessageBase
{
    uint32_t getType() const override { return m_messageType; }
    static bool checkType(uint32_t type) { return type == m_messageType; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_messageType; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    EngineMode mode;

private:
     static inline uint32_t m_messageType = 12;
};

struct CORE_EXPORT SetModeEngineMsgAns : public MessageBase
{
    uint32_t getType() const override { return m_messageType; }
    static bool checkType(uint32_t type) { return type == m_messageType; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_messageType; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

public:
    bool modeChangedSuccess;
    EngineMode mode;

private:
     static inline uint32_t m_messageType = 11;
};

#endif // STARTENGINEMSG_H
