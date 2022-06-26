#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QQmlEngine>

#include "scene/scene.h"

class Engine;
class PluginLoader;
class AbstractPluginInterface;

class AppCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)
    explicit AppCore(QObject *parent = nullptr);
public:
    static AppCore* getInstance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngineBase);
    ~AppCore();

    Scene *scene() const;
    void setScene(Scene *newScene);
    void init(QString appPath);

public slots:
    void start();
    void stop();
signals:
    void sceneChanged();
private:
    void load(AbstractPluginInterface *pluginInstance);

private:
    Scene *m_scene = nullptr;
    Engine *m_engine = nullptr;
    PluginLoader *m_pluginLoader = nullptr;
};

#endif // APPCORE_H
