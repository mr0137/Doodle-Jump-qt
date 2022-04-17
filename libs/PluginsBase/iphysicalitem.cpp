#include <iphysicalitem.h>

IPhysicalItem::IPhysicalItem() {

}

IPhysicalItem::~IPhysicalItem()
{
    while(!m_creators.empty())
    {
        delete m_creators.takeFirst();
    }
}
