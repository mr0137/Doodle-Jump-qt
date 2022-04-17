#ifndef CHANGECOORDSMSG_H
#define CHANGECOORDSMSG_H

#include <messagebase.h>
#include <pluginsbase_global.h>

struct PLUGINSBASE_EXPORT ChangeCoordsMsg : MessageBase
{
    static bool checkType(int type) { return type == m_type; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_type; }
    int getType() const override { return m_type; }
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

    double x;
    double y;
    int m_uid;
private:
    static inline int m_type = 7;
};

struct PLUGINSBASE_EXPORT ChangeCoordsMsgAns : MessageBase
{
    static bool checkType(int type) { return type == m_type; }
    static bool checkType(MessageBase *msg) { return msg->getType() == m_type; }
    int getType() const override { return m_type; }

    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;

    bool success;
    int id;
private:
    static inline int m_type = 8;
};

#endif // CHANGECOORDSMSG_H
