#include "coreplugin_plugin.h"
#include <QDir>
#include <qqml.h>

#include "controllers/doodlercontroller.h"
#include "controllers/slabcontroller.h"
#include "objects/slab.h"
#include "objects/doodler.h"


void CorePlugin::registerTypes(const char *)
{
    // @uri SaveProvider
}

void CorePlugin::init(QString appPath)
{
    m_appPath = appPath;

    createControllerFactory<SlabController>();
    createObjectFactory<Slab>();

    createCollideControllerFactory<DoodlerController>();
    createObjectFactory<Doodler>();

    m_resources.insert("SlabDefault", "Slabdefault");
}
