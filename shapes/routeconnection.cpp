#include "routeconnection.h"
#include "triangleup.h"

RouteConnection::RouteConnection(QPointF from, QPointF to, QColor color)
    : defaultPen(color, getSize() + 2, Qt::SolidLine), currentPen(defaultPen),
      cartesianLine(new QLineF(from, to))
{
    this->setPen(currentPen);
    this->setLine(*cartesianLine);
}


void RouteConnection::setColors(const QColor &color) {
    currentPen.setColor(color);
}

void RouteConnection::setDefaultColors() {
    currentPen.setColor(defaultPen.color());
}

void RouteConnection::setSize(qreal newSize) {
    size = newSize + 2;
    currentPen.setWidth(size);
}

QPen RouteConnection::getPen() {
    return currentPen;
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
