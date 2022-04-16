#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <qqml.h>
#include <QObject>
#include <QPointF>
#include <QVariant>
#include <pluginsbase_global.h>

class PLUGINSBASE_EXPORT SceneItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int sceneID READ sceneID WRITE setSceneID NOTIFY sceneIDChanged)
public:
    explicit SceneItem(QObject *parent = nullptr);

    virtual QVariantMap serialize() { return {}; }
    virtual void deserialize(QVariantMap map) { Q_UNUSED(map) }

    int sceneID() const;
    QString type() const;

    void setSceneID(int newSceneID);
    void setType(const QString &newType);

signals:
    void pressed();
    void typeChanged();
    void sceneIDChanged();

private:
    static inline const int SceneItemQMLRegistration = qmlRegisterType<SceneItem>("PluginsBase", 1, 0, "SceneItem");
    QString m_type = "SceneItem";
    int m_sceneID;
};

#endif // SCENEITEM_H
