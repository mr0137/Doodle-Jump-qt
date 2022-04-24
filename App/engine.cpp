#include "engine.h"
#include <QtConcurrent>
#include <chrono>
#include <ctime>
#include <engineinterface.h>

using namespace std::chrono_literals;

Engine::Engine(QObject *parent) : QObject(parent), lastCreatedPIID(0)
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
        while (this->working) {
            auto now = std::chrono::system_clock::now();
            auto dt = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
            if (dt > delay) {
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
}

CreateItemMsgAns Engine::proceedCreateItemMsg(CreateItemMsg msg)
{
    QString type = msg.objectType;
    CreateItemMsgAns answ;

    AbstractObjectController *controller = controllers[type]->create();
    controller->setPiId(this->lastCreatedPIID);
    qDebug() << msg.objectType << lastCreatedPIID;
    controller->init(&msg, this);

    this->insertController(this->lastCreatedPIID, controller);
    answ.id = this->lastCreatedPIID;
    lastCreatedPIID++;
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
    SetModeEngineMsgAns msgAnswer;
    msgAnswer.modeChangedSuccess = true;
    msgAnswer.mode = msg.mode;
    return msgAnswer;
}

void Engine::setControllers(const QHash<QString, ControllerFactory *> &value)
{
    controllers = value;
}

