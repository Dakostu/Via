#include "routenodedata.h"
#include <QRgb>
#include <QJsonArray>


bool RouteNodeData::isNameChangedByUser() const
{
    return nameChanged;
}

void RouteNodeData::setNameChangedByUser(bool value)
{
    nameChanged = value;
}

RouteNodeData::RouteNodeData()
    : differentStyleFromRoute(false), nameChanged(false), invisible(false)
{

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

int RouteNodeData::getSize() const
{
    return nodeSize;
}

void RouteNodeData::setSize(int value)
{
    nodeSize = value;
}

QColor RouteNodeData::getColor() const
{
    return color;
}

void RouteNodeData::setPos(int newX, int newY) {
    x = newX;
    y = newY;
}

RouteNodeData::RouteNodeData(const QJsonObject &object) {
    fromJSON(object);
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
        color = QColor(object["color"][0].toInt(), object["color"][1].toInt(), object["color"][2].toInt());
        nodeSize = object["nodeSize"].toInt();
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
        routeNodeJSON["color"] = QJsonArray({color.red(), color.green(), color.blue()});
        routeNodeJSON["nodeSize"] = nodeSize;
    }

    return routeNodeJSON;
}


bool RouteNodeData::isStyleDifferentFromRoute() const {
    return differentStyleFromRoute;
}

void RouteNodeData::setColor(QColor newColor) {
    color = newColor;
}

bool RouteNodeData::operator==(const RouteNodeData &other) const {
    return this->x == other.x
            && this->y == other.y
            && this->nodeName == other.nodeName
            && this->nodeLabel == other.nodeLabel
            && this->differentStyleFromRoute == other.differentStyleFromRoute
            && this->invisible == other.invisible
            && this->nameChanged == other.nameChanged
            && this->color == other.color
            && this->nodeSize == other.nodeSize;
}
