#ifndef NODESHAPEABLE_H
#define NODESHAPEABLE_H

#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QGraphicsSimpleTextItem>

class NodeShapeable : public QGraphicsPolygonItem
{

protected:
    int size;
    QBrush fillColor;
    QPen lineColor;
    QGraphicsSimpleTextItem nodeText;

public:
    NodeShapeable(const QVector<QPointF> &points, QBrush brush, QPen pen, QGraphicsItem *scene, QString text);

    int sizeMultiplier(int val);
    int getSize();
    void setSize(int newSize);

    virtual QPointF getCenter() = 0;

};

#endif // NODESHAPEABLE_H
