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
    QGraphicsSimpleTextItem nodeLabel;
    QGraphicsSimpleTextItem extraTextLabel;
    qreal midX;
    qreal midY;

    static constexpr qreal DEFAULT_LENGTH = 9.0;
    static constexpr qreal DEFAULT_EXTRA_LENGTH = 1.0;
    static constexpr qreal FILLCOLOR_LIGHTNESS_THRESHOLD = 0.3;

public:
    NodeShapeable(qreal x, qreal y, QBrush brush, QString text);

    qreal sizeMultiplier(qreal val);
    qreal getSize();
    void setSize(qreal newSize);
    QPointF getCenter();
    QGraphicsSimpleTextItem* getNodeLabel();
    QGraphicsSimpleTextItem* getExtraTextLabel();

    virtual void drawShape() = 0;

};

#endif // NODESHAPEABLE_H
