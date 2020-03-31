#include "routenodedata.h"
#include <QRgb>
#include <QJsonArray>

using namespace Via::Model;

char RouteNodeData::getShapeKey() const
{
    return style;
}

void RouteNodeData::setShapeKey(char value)
{
    style = value;
}

RouteNodeData::RouteNodeData() : x(0), y(0), differentStyleFromRoute(false), nameChanged(false), invisible(false), style(0)
{

}

RouteNodeData::RouteNodeData(const QColor &color) : RouteNodeData() {
    setColors(color);
}

RouteNodeData::RouteNodeData(const QJsonObject &object) : RouteNodeData() {
    fromJSON(object);
}

bool RouteNodeData::isNameChangedByUser() const
{
    return nameChanged;
}

void RouteNodeData::setNameChangedByUser(bool value)
{
    nameChanged = value;
}


int RouteNodeData::getY() const
{
    return y;
}

void RouteNodeData::setY(int value)
{
    y = value;
}

QPointF RouteNodeData::getCenter() const {
    return {qreal(x),qreal(y)};
}

void RouteNodeData::setDifferentStyleFromRoute(bool value)
{
    differentStyleFromRoute = value;
}


QString RouteNodeData::getNodeLabel() const
{
    return nodeLabel;
}

void RouteNodeData::setNodeLabel(const QString &value)
{
    nodeLabel = value;
}

int RouteNodeData::getX() const
{
    return x;
}

void RouteNodeData::setX(int value)
{
    x = value;
}

bool RouteNodeData::getInvisible() const
{
    return invisible;
}

void RouteNodeData::setInvisible(bool value)
{
    invisible = value;
}

void RouteNodeData::setPos(int newX, int newY) {
    x = newX;
    y = newY;
}

void RouteNodeData::fromJSON(const QJsonObject &object) {
    name = object[NODE_NAME_KEY].toString();
    nodeLabel = object[NODE_LABEL_KEY].toString();
    x = object[NODE_X_KEY].toInt();
    y = object[NODE_Y_KEY].toInt();
    differentStyleFromRoute = object[NODE_DIFFERENT_STYLE_KEY].toBool();
    nameChanged = object[NODE_NAME_CHANGED_KEY].toBool();
    invisible = object[NODE_INVISIBLE_KEY].toBool();

    if (differentStyleFromRoute) {
        currentColor = QColor(object[NODE_COLOR_KEY][0].toInt(), object[NODE_COLOR_KEY][1].toInt(), object[NODE_COLOR_KEY][2].toInt());
        elementSize = object[NODE_SIZE_KEY].toInt();
        style = object[NODE_SHAPE_KEY].toInt();
    }

}

QJsonObject RouteNodeData::toJSON() const {
    QJsonObject routeNodeJSON;

    routeNodeJSON[NODE_NAME_KEY] = name;
    routeNodeJSON[NODE_LABEL_KEY] = nodeLabel;
    routeNodeJSON[NODE_X_KEY] = x;
    routeNodeJSON[NODE_Y_KEY] = y;
    routeNodeJSON[NODE_DIFFERENT_STYLE_KEY] = differentStyleFromRoute;
    routeNodeJSON[NODE_NAME_CHANGED_KEY] = nameChanged;
    routeNodeJSON[NODE_INVISIBLE_KEY] = invisible;

    if (differentStyleFromRoute) {
        routeNodeJSON[NODE_COLOR_KEY] = QJsonArray({currentColor.red(), currentColor.green(), currentColor.blue()});
        routeNodeJSON[NODE_SIZE_KEY] = elementSize;
        routeNodeJSON[NODE_SHAPE_KEY] = style;
    }

    return routeNodeJSON;
}


bool RouteNodeData::isStyleDifferentFromRoute() const {
    return differentStyleFromRoute;
}

void RouteNodeData::setColors(const QColor &color) {
    currentColor = color;
}

void RouteNodeData::activateColors() {
    setColors(Qt::white);
}

bool RouteNodeData::operator==(const RouteNodeData &other) const {
    return this->toJSON() == other.toJSON();
}
