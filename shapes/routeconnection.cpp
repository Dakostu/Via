#include "routeconnection.h"
#include "triangleup.h"

using namespace Via::Shapes;

RouteConnection::RouteConnection(QPointF from, QPointF to, const QColor &color)
    : connectionColor(color),
      cartesianLine(new QLineF(from, to))
{    
    elementSize = sizeMultiplier(SIZE_FACTOR) + SIZE_OFFSET;
    activateColors();
    this->setLine(*cartesianLine);
}

QColor RouteConnection::getColors() {
    return connectionColor;
}

void RouteConnection::setColors(const QColor &color) {
    connectionColor = color;
    activateColors();
}

void RouteConnection::activateColors() {
    this->setPen(QPen(connectionColor, getElementSize()));
}

void RouteConnection::setElementSize(int newSize) {
    elementSize = newSize;
    elementSize = sizeMultiplier(SIZE_FACTOR) + SIZE_OFFSET;
    this->setPen(QPen(pen().color(), elementSize));
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
