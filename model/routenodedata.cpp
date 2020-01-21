#include "routenodedata.h"
#include <QRgb>
#include <QJsonArray>

RouteNodeData::RouteNodeData()
{

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
    return size;
}

void RouteNodeData::setSize(int value)
{
    size = value;
}

QColor RouteNodeData::getColor() const
{
    return color;
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
    invisible = object["invisible"].toBool();

    if (differentStyleFromRoute) {
        color = QColor(object["color"][0].toInt(), object["color"][1].toInt(), object["color"][2].toInt());
        size = object["size"].toInt();
    }

}

QJsonObject RouteNodeData::toJSON() const {
    QJsonObject routeNodeJSON;

    routeNodeJSON["nodeName"] = nodeName;
    routeNodeJSON["nodeLabel"] = nodeLabel;
    routeNodeJSON["x"] = x;
    routeNodeJSON["y"] = y;
    routeNodeJSON["differentStyleFromRoute"] = differentStyleFromRoute;
    routeNodeJSON["invisible"] = invisible;

    if (differentStyleFromRoute) {
        routeNodeJSON["color"] = QJsonArray({color.red(), color.green(), color.blue()});
        routeNodeJSON["size"] = size;
    }

    return routeNodeJSON;
}


bool RouteNodeData::isStyleDifferentFromRoute() {
    return differentStyleFromRoute;
}

void RouteNodeData::setColor(QColor &newColor) {
    color = newColor;
}
