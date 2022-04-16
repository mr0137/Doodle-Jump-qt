#ifndef ABSTRACTSERVERINTERFACE_H
#define ABSTRACTSERVERINTERFACE_H

#include <QQmlEngine>
#include <QQmlContext>
#include <factories/sceneitemsfactory.h>
#include "AbstractPluginInterface.h"
#include "pluginsbase_global.h"

class Engine;

class PLUGINSBASE_EXPORT AbstractServerInterface : public AbstractPluginInterface {
public:
    AbstractServerInterface();
    virtual ~AbstractServerInterface();
//    virtual void init(Engine *eng) = 0;
//    virtual void sendData(const QVariantMap&) = 0;
//    virtual void getCommand() = 0;
    virtual void registerStream(QString, std::function<void(QVariantMap)> &) = 0;
//    virtual void

};

Q_DECLARE_INTERFACE(AbstractServerInterface, "com.my.AbstractServerInterface")

#endif // ABSTRACTSERVERINTERFACE_H
