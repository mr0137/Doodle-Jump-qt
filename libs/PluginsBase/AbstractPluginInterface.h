#ifndef ABSTRACTPLUGININTERFACE_H
#define ABSTRACTPLUGININTERFACE_H

#include "pluginsbase_global.h"
#include <QObject>
#include <QVariantList>
#include <enginebase.h>

typedef QMap<QString, QMap<QString, QMap<QString, QString>>> ComponentsMap;

class PLUGINSBASE_EXPORT AbstractPluginInterface {

    QString m_typeName;
public:
    QString typeName() {return m_typeName;}
    void setTypeName(QString value) {if(value == m_typeName) return; m_typeName = value;}
public:
    AbstractPluginInterface();
    virtual ~AbstractPluginInterface();

    virtual void init(EngineBase * engine, QString appPath = "", const QVariantList &depencies = QVariantList()) = 0;
    virtual ComponentsMap getComponents() = 0;

    template<typename Msg, typename Callable>
    void registerPluginEngineCalback(EngineBase*, Callable f);

};

template<typename Msg, typename Callable>
        void AbstractPluginInterface::registerPluginEngineCalback(EngineBase * engine, Callable f)
{
    engine->getInterface()->addConnection<Msg>(f);
}

Q_DECLARE_INTERFACE(AbstractPluginInterface, "com.my.AbstractPluginInterface")

#endif // ABSTRACTPLUGININTERFACE_H
