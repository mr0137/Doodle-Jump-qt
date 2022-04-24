#ifndef ENGINE_H
#define ENGINE_H


#include <QFuture>
#include <QObject>
#include <QTimer>
#include <enginebase.h>

#include <factories/controllerfactory.h>

#include <removeitemmessage.h>
#include <setmodeenginemsg.h>
#include <createitemmessage.h>

class Engine : public QObject, public EngineBase
{
public:
    Engine(QObject *parent = nullptr);
    ~Engine();

    // AbstractEngine interface
public:
    void start();
    void stop();

    void setControllers(const QHash<QString, ControllerFactory *> &value);

protected:
    int lastCreatedPIID;

private:
    CreateItemMsgAns proceedCreateItemMsg(CreateItemMsg msg);
    RemoveItemMessageAns proceedRemoveItemMsg(RemoveItemMessage msg);
    SetModeEngineMsgAns proceedSetEngineModeMsg(SetModeEngineMsg msg);

private:
    QHash<QString, ControllerFactory*> controllers;
    QFuture<void> future;
    QTimer* m_timer;
    bool working = true;
};

#endif // ENGINE_H