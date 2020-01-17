#include "routenodedata.h"
#include <QRgb>
#include <QJsonArray>

RouteNodeData::RouteNodeData()
{

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
