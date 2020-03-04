#include "routenodeshape.h"
#include <QFont>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

using namespace Via::Interfaces;
using namespace Via::Shapes;

void RouteNodeShape::setElementSize(int newSize) {
    ViewCustomizable::setElementSize(newSize);
    this->drawShape();
}

RouteNodeShape::RouteNodeShape(const QPointF point, const QColor &color)
    : QGraphicsPolygonItem({}, nullptr), originX(point.x()), originY(point.y())
{
    this->setBrush(QBrush(color));

    this->setFlag(ItemIsFocusable);
    this->setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);
}

QColor RouteNodeShape::getColors() {
    return this->brush().color();
}

void RouteNodeShape::setColors(const QColor &color) {
    this->setBrush(color);
}

void RouteNodeShape::activateColors() {
    if (this->brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setPen(QPen(Qt::white));
    } else {
        setPen(QPen(Qt::black));
    }
}
