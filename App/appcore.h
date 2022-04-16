#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>

class AppCore : public QObject
{
    Q_OBJECT
    explicit AppCore(QObject *parent = nullptr);
public:
    static AppCore* getInstance();
    static
signals:

};

#endif // APPCORE_H
