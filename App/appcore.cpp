#include "appcore.h"
#include <QGuiApplication>

AppCore::AppCore(QObject *parent)
    : QObject{parent}
{

}

AppCore *AppCore::getInstance()
{
    static AppCore* m_appcore = nullptr;
    if (!m_appcore)
    {
        m_appcore = new AppCore(qApp);
    }
    return m_appcore;
}
