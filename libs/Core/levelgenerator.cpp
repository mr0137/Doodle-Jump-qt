#include "levelgenerator.h"
#include "engineinterface.h"
#include "qrandom.h"
#include <QDateTime>

LevelGenerator::LevelGenerator()
{
    m_randomX.setSeed(0137);
    m_randomY.setSeed(0137);
}

LevelGenerator::~LevelGenerator()
{
    m_file->close();
}

void LevelGenerator::proceed(const QRectF &visualRect)
{
    if (!m_inited)
    {
        createObject("Doodler", {424, 667});
        m_inited = true;
        for (int i = 0; i < 7; i++)
        {
            createObject("Slab", {i * 100 + 8.3 * i, 30});
        }
        m_maxY = 30;
    }
    uint64_t gap = 120;
    if (m_offset + gap < visualRect.y())
    {
        m_offset += gap;
        //! TODO generation without viewRect width (width might be around 8 platforms + 7 spices = 835
        //! if real width would be bigger -> scale all objects
        int x = m_randomX.generate()%(static_cast<int>(visualRect.width()) - 100);
        int y = 0;
        int r = 0;
        do
        {
            y = m_randomY.generate()%static_cast<int>(visualRect.height()) + m_offset;
            r = sqrt(pow(m_maxY - y,2) + pow(x - x, 2));
        }while (r > 600 && y > m_maxY);

        if (y > m_maxY)
        {
            m_maxY = y;
        }
        //TODO different objects spawn due to percentage
        createObject("Slab", QPointF(x, y));
    }

    for (const auto key : m_idHeights.keys())
    {
        if (m_idHeights[key] < m_offset - visualRect.height() * 2)
        {
            m_deleteHandler(key);
        }
    }
}

void LevelGenerator::addGenerateableObjectsTypes(AbstractObjectController *objectTypes, ControllerType controllerType)
{
    switch(controllerType)
    {
    case ControllerType::SLAB:
    {
        m_creatableSlabObjects.append(objectTypes);
        break;
    }
    case ControllerType::MONSTER:
    {
        m_creatableMonsterObjects.append(objectTypes);
        break;
    }
    case ControllerType::DOODLER:
    {
        qDebug() << "Cannot add Doodler to levelGenerator";
        return;
    }
    case ControllerType::GHOST:
    {
        qDebug() << "Cannot add Doodler to levelGenerator";
        return;
    }
    case ControllerType::BULLET:
    {
        qDebug() << "Cannot add Doodler to levelGenerator";
        return;
    }
    case ControllerType::POWERUP:
    {
        m_creatablePowerUPObjects.append(objectTypes);
        break;
    }
    }
}

void LevelGenerator::setCreateHandler(const std::function<uint32_t (QString, QPointF)> &createHandler)
{
    m_createHandler = createHandler;
}

void LevelGenerator::setDeleteHandler(const std::function<bool(uint32_t)> &deleteHandler)
{
    m_deleteHandler = deleteHandler;
}

void LevelGenerator::createObject(QString type, QPointF pos)
{
    uint32_t id = m_createHandler(type, pos);
    if (m_inited)
    {
        m_idHeights[id] = pos.y();
    }
}
