#ifndef CREATEPIMSG_H
#define CREATEPIMSG_H

#include <messagebase.h>
#include <pluginsbase_global.h>
#include <QDataStream>
#include <QString>

struct PLUGINSBASE_EXPORT CreatePIMsg : MessageBase
{
    private: inline static int m_type = 1;\
    public: int getType() const override {return m_type;}\
    static bool checkType(int type) {return type == m_type;}\
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}

    double position[3];
    double velocity;
    double angle;
    QString typeOfObject;
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;
};

struct PLUGINSBASE_EXPORT CreatePIMsgAns : MessageBase {
    private: inline static int m_type = 2;\
    public: int getType() const override {return m_type;}\
    static bool checkType(int type) {return type == m_type;}\
    static bool checkType(MessageBase *msg) {return msg->getType() == m_type;}
    int createdId;
    double position[3];
    double velocity;
    double angle;
    QString typeOfObject;
    void serialize(QDataStream *) const override;
    void deserialize(QDataStream *) override;
};

#endif // CREATEPIMSG_H
