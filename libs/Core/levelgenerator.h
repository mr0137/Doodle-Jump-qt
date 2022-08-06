#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <QList>
#include <QMap>
#include <functional>
#include "abstractobjectcontroller.h"
#include "core_global.h"
#include <QFile>

class EngineInterface;

class CORE_EXPORT RandGenerator
{
public:
    void setSeed(uint32_t seed) { m_seed = QString::number(seed); }
    quint32 generate()
    {
        m_seed = QString::number(std::hash<std::string>{}(m_seed.toStdString()));
        return m_seed.midRef(0,m_seed.length()/2).toUInt();
    }
private:
    QString m_seed;
};

struct CORE_EXPORT ObjectData
{
    double xPos;
    double yPos;
    QRectF boundingRect;
};

class CORE_EXPORT LevelGenerator
{
public:
    LevelGenerator();
    ~LevelGenerator();
    void proceed(const QRectF &visualRect);
    void addGenerateableObjectsTypes(AbstractObjectController* objectTypes, ControllerType controllerType);

    void setCreateHandler(const std::function<uint32_t (QString, QPointF)> &createHandler);
    void setDeleteHandler(const std::function<bool(uint32_t)> &deleteHandler);
    void setBoundingRectGetter(const std::function<QRectF(QString)> &boundingRectGetter);
private:
    void createObject(QString type, QPointF pos);

private:
    std::function<uint32_t(QString type, QPointF)> m_createHandler = nullptr;
    std::function<bool(uint32_t)> m_deleteHandler = nullptr;
    std::function<QRectF(QString)> m_boundingRectGetter = nullptr;

    QList<AbstractObjectController*> m_creatableSlabObjects;
    QList<AbstractObjectController*> m_creatableMonsterObjects;
    QList<AbstractObjectController*> m_creatablePowerUPObjects;

    QMap<uint32_t, ObjectData> m_objects;

    int64_t m_offset = 0;
    bool m_inited = false;
    int m_maxY = 0;
    RandGenerator m_randomX;
    RandGenerator m_randomY;
    QFile* m_file;
};

#endif // LEVELGENERATOR_H
