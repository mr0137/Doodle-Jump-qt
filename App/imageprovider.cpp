#include "imageprovider.h"
#include <QDebug>

ImageProvider::ImageProvider(QObject *parent)
    : QObject(parent)
{

}

ImageProvider::~ImageProvider()
{
    QStringList keys = m_images.keys();

    for (const auto &key : keys)
    {
        auto image = m_images[key];
        m_images.remove(key);
        delete image;
    }
}

void ImageProvider::registerImage(QString id, QString path, double imageWidth, double imageHeight)
{
    if (m_images.contains(id))
    {
        qDebug() << "Cannot register image: id already exist!";
        return;
    }

    auto image = new QImage(path);
    if (image->isNull())
    {
        qDebug() << "Cannot register image: undefined path!";
        delete image;
        return;
    }

    if (imageWidth != 0 && imageHeight != 0)
    {
        image->scaledToHeight(imageHeight, Qt::SmoothTransformation);
        image->scaledToWidth(imageWidth, Qt::SmoothTransformation);
    }

    m_images.insert(id, image);
}

QImage *ImageProvider::getImage(QString id)
{
    if (m_images.keys().contains(id))
    {
        return m_images[id];
    }
    return nullptr;
}
