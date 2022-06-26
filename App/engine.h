#ifndef ENGINE_H
#define ENGINE_H

#include <QFuture>
#include <QObject>
#include <QTimer>
#include <enginebase.h>
#include <messages/createitemmessage.h>
#include <messages/removeitemmessage.h>
#include <messages/setmodeenginemsg.h>
#include <factories/controllerfactory.h>

class Engine : public QObject, public EngineBase
{
public:
    Engine(QObject *parent = nullptr);
    ~Engine();

    void start();
    void stop();

    void addControllerFactories(const QList<ControllerFactory *> *value);
    void addCollideControllerFactories(const QList<ControllerFactory *> *value);

private:
    CreateItemMsgAns proceedCreateItemMsg(CreateItemMsg msg);
    RemoveItemMessageAns proceedRemoveItemMsg(RemoveItemMessage msg);
    SetModeEngineMsgAns proceedSetEngineModeMsg(SetModeEngineMsg msg);

    uint32_t createObject(QString type, QPoint pos);
    bool deleteObject(uint32_t id);

private:
    QHash<QString, ControllerFactory*> m_objectControllerFactories;
    QHash<QString, ControllerFactory*> m_collideControllerFactories;
    QFuture<void> future;
    QFuture<void> m_interfaceProceeder;
    QTimer* m_timer;
    bool working = true;
};

#endif // ENGINE_H
