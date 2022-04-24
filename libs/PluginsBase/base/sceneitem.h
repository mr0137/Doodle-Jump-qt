#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <qqml.h>
#include <QObject>
#include <QPointF>
#include <QVariant>
#include <pluginsbase_global.h>
#include <QRectF>

class PLUGINSBASE_EXPORT SceneItem : public QObject
{
    Q_OBJECT
public:
    explicit SceneItem(uint32_t id, QString type, QObject *parent = nullptr);

    QString type() const;
    void setType(const QString &newType);
    uint32_t id() const;

    double x() const;
    double y() const;
    double width() const;
    double height() const;

    const QString &imagePath() const;
    QRectF boundingRect() const;

    enum RemovingState : uint8_t{
        NONE,
        PREPARE,
        READY
    };

    RemovingState removeState();

private:
    QString m_type = "SceneItem";
    int m_sceneID;
    uint32_t m_id;
    double m_x;
    double m_y;
    double m_width;
    double m_height;
    QString m_imagePath;
    RemovingState m_removingState = NONE;
    QRectF m_boundingRect;
};

#endif // SCENEITEM_H
