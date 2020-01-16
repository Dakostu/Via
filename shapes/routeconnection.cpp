#include "routeconnection.h"
#include "triangleup.h"

RouteConnection::RouteConnection(RouteNode *fromNode, RouteNode *toNode, QColor color)
    : from(fromNode), to(toNode), defaultPen(color), currentPen(defaultPen)
{
    setSize(from->getSize());

    auto fromCenter = from->boundingRect().center();
    auto toCenter = to->boundingRect().center();

    setPoints(fromCenter, toCenter);

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
