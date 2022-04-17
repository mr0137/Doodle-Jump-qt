#include "itemsfactory.h"

ItemsFactory::ItemsFactory(const std::map<std::string, std::function<AbstractObjectController*()>> &controllers)
{
    m_controllersCreator = controllers;
}

AbstractObjectController *ItemsFactory::createController(std::string cName)
{
    auto search = m_controllersCreator.find(cName);
    if(search != m_controllersCreator.end())
        return search->second();
    return nullptr;
}

void ItemsFactory::registerController(std::string cType, std::function<AbstractObjectController* ()> controller)
{
    m_controllersCreator.insert({cType, controller});
}
