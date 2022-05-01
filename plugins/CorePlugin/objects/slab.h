#ifndef SLABDEFAULT_H
#define SLABDEFAULT_H

#include <base/sceneitem.h>
#include <QObject>

class Slab : public SceneItem
{
public:
    explicit Slab(QObject *parent = nullptr);
};

#endif // SLABDEFAULT_H
