#include "itemsfactory.h"

ItemsFactory::ItemsFactory()
{

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
