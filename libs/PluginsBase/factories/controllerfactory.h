#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include <QObject>
#include <pluginsbase_global.h>
#include <abstractobjectcontroller.h>

class PLUGINSBASE_EXPORT ControllerFactory : public QObject
{
    Q_OBJECT
public:
    ControllerFactory(std::function<AbstractObjectController*()> cr): m_creator(cr) {}
    AbstractObjectController *create(){ return m_creator();  }
private:
    std::function<AbstractObjectController*()> m_creator = nullptr;
};

#endif // CONTROLLERFACTORY_H
