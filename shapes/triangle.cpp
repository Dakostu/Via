#include "triangle.h"

using namespace Via::Shapes;

Triangle::Triangle(const QPointF point, const QColor &color, qreal offsetX, qreal offsetY) :
    RouteNodeShape(point, color),
    OFFSET_X(offsetX), OFFSET_Y(offsetY)
{

}


QPointF Triangle::getCenter() {
    auto center = RouteNodeShape::getCenter();
    center += {OFFSET_X, OFFSET_Y};

    return center;
}
