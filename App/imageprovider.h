#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QHash>
#include <QImage>
#include <QObject>
#include <QString>

class ImageProvider : public QObject
{
    Q_OBJECT
public:
    explicit ImageProvider(QObject *parent = nullptr);
    ~ImageProvider();
    void registerImage(QString id, QString path, double imageWidth = 0, double imageHeight = 0);
    QImage* getImage(QString id);
private:
    QHash<QString, QImage*> m_images;
};

#endif // IMAGEPROVIDER_H
