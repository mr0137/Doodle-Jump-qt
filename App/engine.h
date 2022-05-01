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

private:
    QHash<QString, ControllerFactory*> m_objectControllerFactories;
    QHash<QString, ControllerFactory*> m_collideControllerFactories;
    QFuture<void> future;
    QTimer* m_timer;
    bool working = true;
};

#endif // ENGINE_H
