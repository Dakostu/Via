#ifndef NODESHAPEABLE_H
#define NODESHAPEABLE_H


#include "../interfaces/viewcustomizable.h"
#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QGraphicsSimpleTextItem>

class NodeShapeable : public QGraphicsPolygonItem, public ViewCustomizable
{

protected:
    static constexpr qreal DEFAULT_LENGTH = 9.0;
    static constexpr qreal DEFAULT_EXTRA_LENGTH = 1.0;    
    qreal originX;
    qreal originY;

public:
    NodeShapeable(qreal x, qreal y, QBrush brush);

    QPointF getCenter();

    virtual void setSize(qreal newSize) override;
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void drawShape() = 0;


};

#endif // NODESHAPEABLE_H
