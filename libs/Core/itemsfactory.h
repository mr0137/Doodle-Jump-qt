#ifndef ITEMSFACTORY_H
#define ITEMSFACTORY_H

#include "abstractobjectcontroller.h"
#include "core_global.h"

class CORE_EXPORT ItemsFactory
{
public:
    ItemsFactory() = default;
    ItemsFactory(const std::map<std::string, std::function<AbstractObjectController*()>>&);

    AbstractObjectController *createController(std::string);
    void registerController(std::string, std::function<AbstractObjectController*()> controller);

private:
    std::map<std::string, std::function<AbstractObjectController*()>> m_controllersCreator;
};



#endif // ITEMSFACTORY_H
