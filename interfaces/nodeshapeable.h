#ifndef NODESHAPEABLE_H
#define NODESHAPEABLE_H

#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QGraphicsSimpleTextItem>

class NodeShapeable : public QGraphicsPolygonItem
{

protected:
    qreal size;
    QBrush fillColor;
    QPen lineColor;
    QGraphicsSimpleTextItem nodeText;
    qreal midX;
    qreal midY;

    static constexpr qreal DEFAULT_LENGTH = 9.0;
    static constexpr qreal DEFAULT_EXTRA_LENGTH = 1.0;

public:
    NodeShapeable(qreal x, qreal y, QBrush brush, QPen pen, QString text);

    qreal sizeMultiplier(qreal val);
    qreal getSize();
    void setSize(qreal newSize);
    QPointF getCenter();
    QGraphicsSimpleTextItem* getText();

    virtual void drawShape() = 0;

};

#endif // NODESHAPEABLE_H
