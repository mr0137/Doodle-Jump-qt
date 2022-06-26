#ifndef SLABDEFAULT_H
#define SLABDEFAULT_H

#include <base/sceneitem.h>
#include <messagenegotiator.h>
#include <QObject>
#include <messages/changecoordsmsg.h>

class Slab : public SceneItem
{
public:
    explicit Slab(QObject *parent = nullptr);
    ~Slab();
private:
    ChangeCoordsMsgAns proceedCreateItemMsg(ChangeCoordsMsg msg);

private:
    MessageNegotiator *m_messageNegotiator;
};

#endif // SLABDEFAULT_H
