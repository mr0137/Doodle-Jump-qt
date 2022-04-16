#ifndef ITEMSFACTORY_H
#define ITEMSFACTORY_H

#include "abstractobjectcontroller.h"
#include "core_global.h"
class CORE_EXPORT ItemsFactory
{
public:
    ItemsFactory();
    std::map<std::string, std::function<AbstractObjectController*()>> m_controllersCreator;

    //!
    //! \brief Creates controller which is created with \a m_controllersCretors[type]
    //! \return Created controller
    //!
    AbstractObjectController * createController(std::string);

    //!
    //! \brief Register controller creator callback
    //! \param controller
    //!
    void registerController(std::string, std::function<AbstractObjectController*()> controller);

    //    std::function<void(std::string)>
};



#endif // ITEMSFACTORY_H
