#include "pluginloader.h"

PluginLoader::PluginLoader(const QString &appPath, QObject *parent) : QObject(parent), m_appPath(appPath)
{

}

QObject *PluginLoader::load(QString libname)
{
    auto d = QDir::current();
#ifdef QT_NO_DEBUG
    d.cd( appPath + "/plugins/" + libname + "/");
#else
    d.cd( m_appPath + "/bin/plugins/" + libname + "/");
#endif
#ifdef WIN64
    QString path = QUrl(d.absolutePath() + "/" + libname + ".dll").path();
#else
    QString path = QUrl(d.absolutePath() + "/lib" + libname + ".so").path();
#endif
    auto plugin = new QPluginLoader(path);
    plugin->load();
    if (!plugin->isLoaded()) {
        qDebug() << "ERROR while opening plugin: " << plugin->errorString() << path;
    }
    return plugin->instance();
}

bool PluginLoader::unload(const QString &name)
{
    if (m_instancesRegistry.contains(name))
    {
        return m_instancesRegistry[name]->unload();
    }
    return false;
}
