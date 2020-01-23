#include "routenodedata.h"
#include <QRgb>
#include <QJsonArray>

RouteNodeData::RouteNodeData() : ViewCustomizable(),
    differentStyleFromRoute(false), nameChanged(false), invisible(false)
{

}

RouteNodeData::RouteNodeData(const QJsonObject &object) {
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

void RouteNodeData::setDifferentStyleFromRoute(bool value)
{
    differentStyleFromRoute = value;
}

QString RouteNodeData::getNodeName() const
{
    return nodeName;
}

void RouteNodeData::setNodeName(const QString &value)
{
    nodeName = value;
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

QColor RouteNodeData::getColor() const
{
    return nodeColor;
}

void RouteNodeData::setPos(int newX, int newY) {
    x = newX;
    y = newY;
}

void RouteNodeData::fromJSON(const QJsonObject &object) {
    nodeName = object["nodeName"].toString();
    nodeLabel = object["nodeLabel"].toString();
    x = object["x"].toInt();
    y = object["y"].toInt();
    differentStyleFromRoute = object["differentStyleFromRoute"].toBool();
    nameChanged = object["nameChanged"].toBool();
    invisible = object["invisible"].toBool();

    if (differentStyleFromRoute) {
        nodeColor = QColor(object["color"][0].toInt(), object["color"][1].toInt(), object["color"][2].toInt());
        elementSize = object["nodeSize"].toInt();
    }

}

QJsonObject RouteNodeData::toJSON() const {
    QJsonObject routeNodeJSON;

    routeNodeJSON["nodeName"] = nodeName;
    routeNodeJSON["nodeLabel"] = nodeLabel;
    routeNodeJSON["x"] = x;
    routeNodeJSON["y"] = y;
    routeNodeJSON["differentStyleFromRoute"] = differentStyleFromRoute;
    routeNodeJSON["nameChanged"] = nameChanged;
    routeNodeJSON["invisible"] = invisible;

    if (differentStyleFromRoute) {
        routeNodeJSON["color"] = QJsonArray({nodeColor.red(), nodeColor.green(), nodeColor.blue()});
        routeNodeJSON["nodeSize"] = elementSize;
    }

    return routeNodeJSON;
}


bool RouteNodeData::isStyleDifferentFromRoute() const {
    return differentStyleFromRoute;
}

void RouteNodeData::setColors(const QColor &color) {
    nodeColor = color;
}

void RouteNodeData::setDefaultColors() {
    setColors(Qt::white);
}

bool RouteNodeData::operator==(const RouteNodeData &other) const {
    return this->x == other.x
            && this->y == other.y
            && this->nodeName == other.nodeName
            && this->nodeLabel == other.nodeLabel
            && this->differentStyleFromRoute == other.differentStyleFromRoute
            && this->invisible == other.invisible
            && this->nameChanged == other.nameChanged
            && this->nodeColor == other.nodeColor
            && this->elementSize == other.elementSize;
}
