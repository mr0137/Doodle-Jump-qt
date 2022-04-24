#ifndef SLABDEFAULT_H
#define SLABDEFAULT_H

#include <base/sceneitem.h>
#include <QObject>

class SlabDefault : public SceneItem
{
public:
    explicit SlabDefault(QObject *parent = nullptr);
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }

};

#endif // SLABDEFAULT_H
