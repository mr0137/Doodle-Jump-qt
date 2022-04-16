#ifndef CREATEITEMMSG_H
#define CREATEITEMMSG_H

#include <messagebase.h>
#include "../../pluginsbase_global.h"
#include <array>
#include <QString>
#include <QDataStream>

struct PLUGINSBASE_EXPORT CreateItemMsg : public MessageBase
{

private: inline static int m_type = 19;\
public: int getType() const override {return m_type;}\
static bool checkType(int type) {return type == m_type;}\
static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    CreateItemMsg();

    double position[3];
    int id;
    int controllerId;

    double velocity;
    double angle;
    std::string typeOfObject;
    std::string color;

    // MessageBase interface
public:
    void serialize(QDataStream *s) const override;
    void deserialize(QDataStream *s) override;
};

struct PLUGINSBASE_EXPORT CreateItemMsgAns : public MessageBase
{

public:
    int getType() const override {return m_type;}
    static bool checkType(int type) {return type == m_type;}
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    CreateItemMsgAns();

    double position[3];
    int controllerId;
private:
    inline static int m_type = 20;
};

#endif // CREATEITEMMSG_H
