#include "slab.h"

Slab::Slab(QObject *parent)
    : SceneItem(parent)
{
    m_type = "SlabDefault";
    m_width = 100;
    m_height = 30;
    m_messageNegotiator = new MessageNegotiator();
    m_messageNegotiator->registerMsgHandler(&Slab::proceedCreateItemMsg, this);
}

Slab::~Slab()
{
    delete m_messageNegotiator;
}

ChangeCoordsMsgAns Slab::proceedCreateItemMsg(ChangeCoordsMsg msg)
{
    ChangeCoordsMsgAns ans;
    ans.success = true;
    return ans;
}
