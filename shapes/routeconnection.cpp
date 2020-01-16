#include "routeconnection.h"
#include "triangleup.h"

RouteConnection::RouteConnection(QPointF from, QPointF to, QColor color)
    : defaultPen(color),
      cartesianLine(new QLineF(from, to))
{    
    this->setPen(QPen(color, sizeMultiplier(SIZE_FACTOR) + SIZE_OFFSET));
    this->setLine(*cartesianLine);
}


void RouteConnection::setColors(const QColor &color) {
    this->pen().setColor(color);
}

void RouteConnection::setDefaultColors() {
    this->pen().setColor(defaultPen.color());
}

void RouteConnection::setSize(qreal newSize) {
    size = newSize;
    size = sizeMultiplier(SIZE_FACTOR) + SIZE_OFFSET;
    this->setPen(QPen(pen().color(), size));
}

void RouteConnection::setNewPosition(QPointF p1, QPointF p2) {
    cartesianLine->setP1(p1);
    cartesianLine->setP2(p2);
    this->setLine(*cartesianLine);
}

QPointF RouteConnection::p1() {
    return cartesianLine->p1();
}

QPointF RouteConnection::p2() {
    return cartesianLine->p2();
}
