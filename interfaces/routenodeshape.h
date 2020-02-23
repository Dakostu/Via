#ifndef NODESHAPEABLE_H
#define NODESHAPEABLE_H


#include "../interfaces/viewcustomizable.h"
#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QGraphicsSimpleTextItem>

namespace Via::Interfaces {

class RouteNodeShape : public QGraphicsPolygonItem, public ViewCustomizable
{

protected:
    static constexpr qreal DEFAULT_LENGTH = 9.0;
    static constexpr qreal DEFAULT_EXTRA_LENGTH = 1.0;    
    qreal originX;
    qreal originY;

public:
    RouteNodeShape(qreal x, qreal y, const QColor &color);

    QColor getColors();

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;
    void activateColors() override;

    virtual void drawShape() = 0;
    virtual char getShapeKey() = 0;

};

}

#endif // NODESHAPEABLE_H
