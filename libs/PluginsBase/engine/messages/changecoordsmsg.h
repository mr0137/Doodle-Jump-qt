#ifndef CHANGECOORDSMSG_H
#define CHANGECOORDSMSG_H

#include <messagebase.h>
#include <pluginsbase_global.h>

struct PLUGINSBASE_EXPORT ChangeCoordsMsg : MessageBase {
    private: inline static int m_type = 7;\
    public: int getType() const override {return m_type;}\
    static bool checkType(int type) {return type == m_type;}\
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    double x;
    double y;
    double z;
    int m_uid;
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;
};

struct PLUGINSBASE_EXPORT ChangeCoordsMsgAns : MessageBase {
    private: inline static int m_type = 8;\
    public: int getType() const override {return m_type;}\
    static bool checkType(int type) {return type == m_type;}\
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    bool success;
    int id;
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;
};

#endif // CHANGECOORDSMSG_H
