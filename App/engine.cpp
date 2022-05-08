#include "engine.h"
#include <QtConcurrent>
#include <chrono>
#include <ctime>
#include <engineinterface.h>

using namespace std::chrono_literals;

Engine::Engine(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        m_interface->proceed();
    });

    messageNegotiator->registerMsgHandler(&Engine::proceedCreateItemMsg, this);
    messageNegotiator->registerMsgHandler(&Engine::proceedRemoveItemMsg, this);
    messageNegotiator->registerMsgHandler(&Engine::proceedSetEngineModeMsg, this);
}

Engine::~Engine()
{
    future.cancel();
    future.waitForFinished();
}

void Engine::start()
{
    future = QtConcurrent::run([this](){
        const int delay = 1000; // microsec
        auto start = std::chrono::system_clock::now();
        auto last = std::chrono::system_clock::now();
        while (this->working)
        {
            auto now = std::chrono::system_clock::now();
            auto dt = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
            if (dt > delay)
            {
                auto t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count();
                proceed(t1, dt);
                last = now;
            }
        }
    });

    m_timer->start(100);
}

void Engine::stop()
{
    working = false;
    future.cancel();
    future.waitForFinished();
}

void Engine::addControllerFactories(const QList<ControllerFactory *> *value)
{
    for (auto* controller : *value)
    {
        m_objectControllerFactories.insert(controller->type(), controller);
    }
}

void Engine::addCollideControllerFactories(const QList<ControllerFactory *> *value)
{
    for (auto* controller : *value)
    {
        m_collideControllerFactories.insert(controller->type(), controller);
    }
}

void Engine::addLevelObjectCreators(const QList<ControllerFactory *> *value)
{

}

CreateItemMsgAns Engine::proceedCreateItemMsg(CreateItemMsg msg)
{
    QString type = msg.objectType;

    CreateItemMsgAns answ;
    answ.objectType = msg.objectType;
    answ.id = createObject(type, {msg.x, msg.y});

    qDebug() << msg.objectType << lastCreatedPIID;
    return answ;
}

RemoveItemMessageAns Engine::proceedRemoveItemMsg(RemoveItemMessage msg)
{
    RemoveItemMessageAns ans;
    for (uint32_t id : msg.ids) {
        if(!removeController(id)) {
            ans.modeChangedSuccess = false;
            return ans;
        }
    }
    ans.modeChangedSuccess = true;
    return ans;
}

SetModeEngineMsgAns Engine::proceedSetEngineModeMsg(SetModeEngineMsg msg)
{
    if(msg.mode == START)
    {
        this->doMath = true;
    }

    if(msg.mode == PAUSE || msg.mode == STOP)
    {
        this->doMath = false;
    }

    if(msg.mode == STOP)
    {
        for (auto p : m_objectControllers)
        {
            delete p.second;
        }
        m_objectControllers.clear();
        lastCreatedPIID = -1;
    }

    SetModeEngineMsgAns msgAnswer;
    msgAnswer.modeChangedSuccess = true;
    msgAnswer.mode = msg.mode;
    return msgAnswer;
}

uint32_t Engine::createObject(QString type, QPoint pos)
{
    ControllerFactory* factory = nullptr;
    factory = *m_objectControllerFactories.find(type);
    if (factory == nullptr)
    {
        factory = *m_collideControllerFactories.find(type);
    }

    if (factory == nullptr)
    {
        return -1;
    }

    AbstractObjectController *controller = factory->create();
    lastCreatedPIID++;
    controller->setPiId(lastCreatedPIID);

    controller->init(pos);

    insertController(lastCreatedPIID, controller);
    return lastCreatedPIID;
}

