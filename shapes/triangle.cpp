#include "triangle.h"

using namespace Via::Shapes;

Triangle::Triangle(const QPointF point, const QColor &color, qreal offsetX, qreal offsetY) :
    RouteNodeShape(point, color),
    OFFSET_X(offsetX), OFFSET_Y(offsetY)
{

}


QPointF Triangle::getCenterOfShape() {
    auto center = RouteNodeShape::getCenterOfShape();
    center += {OFFSET_X, OFFSET_Y};

    return center;
}
