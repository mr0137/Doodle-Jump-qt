#ifndef REMOVEITEMMESSAGE_H
#define REMOVEITEMMESSAGE_H

#include <messagebase.h>
#include <vector>
#include <pluginsbase_global.h>
#include <QDataStream>

struct PLUGINSBASE_EXPORT RemoveItemMessage : MessageBase
{
    private: inline static int m_type = 3;\
    public: int getType() const override {return m_type;}\
    static bool checkType(int type) {return type == m_type;}\
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    std::vector<int> ids;
    //int removeId;
    RemoveItemMessage();
    void serialize(QDataStream *s) const override;
    void deserialize(QDataStream *s) override;
};

struct PLUGINSBASE_EXPORT RemoveItemMessageAns : MessageBase {
    private: inline static int m_type = 4;\
    public: int getType() const override {return m_type;}\
    static bool checkType(int type) {return type == m_type;}\
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    bool removed;
    void serialize(QDataStream *s) const override;
    void deserialize(QDataStream *s) override;
};

#endif // REMOVEITEMMESSAGE_H
