#ifndef ITEMSTARTMSG_H
#define ITEMSTARTMSG_H

#include <messagebase.h>
#include <pluginsbase_global.h>
#include <QString>
#include <QDataStream>

struct PLUGINSBASE_EXPORT ItemStartMsg : public MessageBase
{
private: inline static int m_type = 17;\
public: int getType() const override {return m_type;}\
static bool checkType(int type) {return type == m_type;}\
static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    QString itemName;
    int id;
void serialize(QDataStream *) const override;
void deserialize(QDataStream *) override;
};

struct PLUGINSBASE_EXPORT ItemStopMsg : public MessageBase
{
private: inline static int m_type = 18;\
public: int getType() const override {return m_type;}\
static bool checkType(int type) {return type == m_type;}\
static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    int id;
    QString itemName;
void serialize(QDataStream *) const override;
void deserialize(QDataStream *) override;
};

#endif // ITEMSTARTMSG_H
