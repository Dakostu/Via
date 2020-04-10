#ifndef NODESHAPEABLE_H
#define NODESHAPEABLE_H

#include "../interfaces/shapekeyable.h"
#include "../interfaces/viewcustomizable.h"

#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QGraphicsSimpleTextItem>

namespace Via::Shapes {

class RouteNodeShape : public QGraphicsPolygonItem,
                       public Via::Interfaces::ViewCustomizable,
                       public Via::Interfaces::ShapeKeyable
{

protected:
    static constexpr qreal DEFAULT_LENGTH = 9.0;
    static constexpr qreal DEFAULT_EXTRA_LENGTH = 1.0;    
    qreal originX;
    qreal originY;

public:
    RouteNodeShape(const QPointF point, const QColor &color);

    QColor getColors();

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;
    void activateColors() override;

    virtual void drawShape() = 0;
    QPointF getCenterOfBoundingBox();
    virtual QPointF getCenterOfShape();

};

}

#endif // NODESHAPEABLE_H
