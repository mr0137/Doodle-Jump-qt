#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <qqml.h>
#include <QObject>
#include <QPoint>
#include <QVariant>
#include <pluginsbase_global.h>
#include <QRectF>

class PLUGINSBASE_EXPORT SceneItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint32_t id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(bool movable READ movable WRITE setMovable NOTIFY movableChanged)
public:
    explicit SceneItem(QObject *parent = nullptr);

    QString type() const;
    void setType(const QString &newType);
    uint32_t id() const;
    void setId(uint32_t newId);

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

    RemovingState removingState();
    void setRemovingState(RemovingState newState);

    void setX(double newX);
    void setY(double newY);

    bool movable() const;
    void setMovable(bool newMovable);

signals:
    void idChanged();
    void xChanged();
    void yChanged();

    void movableChanged();

protected:
    QString m_type = "SceneItem";
    uint32_t m_id;
    double m_x;
    double m_y;
    double m_width;
    double m_height;
    QString m_imagePath;
    RemovingState m_removingState = NONE;
    QRectF m_boundingRect;
    bool m_movable = false;
};

#endif // SCENEITEM_H
