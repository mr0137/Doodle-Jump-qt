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

    });
    m_lastCreatedPIID = 0;
    //messageNegotiator->registerMsgHandler(&Engine::proceedCreateItemMsg, this);
    //messageNegotiator->registerMsgHandler(&Engine::proceedRemoveItemMsg, this);
    messageNegotiator->registerMsgHandler(&Engine::proceedSetEngineModeMsg, this);

    m_levelGenerator->setCreateHandler([this](QString name, QPointF pos){
       return createObject(name, pos);
    });

    m_levelGenerator->setDeleteHandler([this](uint32_t id){
        return deleteObject(id);
    });
}

Engine::~Engine()
{
    future.cancel();
    m_interfaceProceeder.cancel();
    m_interfaceProceeder.waitForFinished();
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

    m_interfaceProceeder = QtConcurrent::run([this](){
        while (this->working)
        {
            m_interface->proceed();
        }
    });

    //m_timer->start(5);
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

CreateItemMsgAns Engine::proceedCreateItemMsg(CreateItemMsg msg)
{
    QString type = msg.objectType;

    CreateItemMsgAns answ;
    answ.objectType = msg.objectType;
    answ.id = createObject(type, QPointF{msg.x, msg.y});
    qDebug() << msg.objectType << m_lastCreatedPIID;
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
        m_lastCreatedPIID = -1;
    }

    SetModeEngineMsgAns msgAnswer;
    msgAnswer.modeChangedSuccess = true;
    msgAnswer.mode = msg.mode;
    return msgAnswer;
}

uint32_t Engine::createObject(QString type, QPointF pos)
{
    ControllerFactory* factory = nullptr;
    auto it = m_objectControllerFactories.find(QString(type + QString("Controller")));
    if (it == m_objectControllerFactories.end())
    {
        it = m_collideControllerFactories.find(QString(type + QString("Controller")));
        if (it == m_collideControllerFactories.end())
        {
            qDebug() << "error, controller" << type << "doesn't exist";
            return -1;
        }
    }
    factory = it.value();

    AbstractObjectController *controller = factory->create();
    m_lastCreatedPIID++;
    controller->setPiId(m_lastCreatedPIID);
    controller->setEngineBase(this);
    controller->init(pos);

    insertController(m_lastCreatedPIID, controller);

    CreateItemMsg msg;
    msg.x = pos.x();
    msg.y = pos.y();
    msg.width = controller->getBoundingRect().width();
    msg.height = controller->getBoundingRect().height();
    msg.objectType = type;
    msg.id = m_lastCreatedPIID;
    m_interface->sendFromEngine(msg, m_lastCreatedPIID);

    qDebug() << "Engine" << msg.id;

    return m_lastCreatedPIID;
}

bool Engine::deleteObject(uint32_t id)
{
    //TODO add removing
    return false;
}

