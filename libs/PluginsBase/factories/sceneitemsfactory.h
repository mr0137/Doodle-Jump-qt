#ifndef SCENEITEMSFACTORY_H
#define SCENEITEMSFACTORY_H

#include <QObject>
#include <pluginsbase_global.h>
#include <base/sceneitem.h>
#include <QVariantMap>

class PLUGINSBASE_EXPORT SceneItemsFactory : public QObject
{
    Q_OBJECT
public:
    SceneItemsFactory(std::function<SceneItem*()> cr) : m_creator(cr) {}

    SceneItem *create(QVariantMap params){ auto item = m_creator(); setParams(item, params); return item; }
private:
    void setParams(QObject *obj, QVariantMap params)
    {
        QMapIterator<QString, QVariant> iter(params);
        QMap<QString, int> properties;

        for (int i = 0, size = obj->metaObject()->propertyCount(); i < size; i++)
        {
            auto p = obj->metaObject()->property(i);
            properties.insert(p.name(), i);
        }

        while (iter.hasNext())
        {
            auto p = iter.next();
            if (properties.contains(p.key()))
            {
                obj->metaObject()->property(properties[p.key()]).write(obj, p.value());
            }
        }
    }

private:
    std::function<SceneItem*()> m_creator = nullptr;
};

#endif // SCENEITEMSFACTORY_H
