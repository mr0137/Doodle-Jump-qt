#include "slabdefault.h"

SlabDefault::SlabDefault(QObject *parent)
    : SceneItem(parent)
{
    m_type = "SlabDefault";
    m_width = 100;
    m_height = 30;
}
