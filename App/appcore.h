#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QQmlEngine>

#include <scene/scene.h>

class AppCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)
    explicit AppCore(QObject *parent = nullptr);
public:
    static AppCore* getInstance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngineBase);

    Scene *scene() const;
    void setScene(Scene *newScene);

signals:
    void sceneChanged();

private:
    Scene *m_scene = nullptr;
};

#endif // APPCORE_H
