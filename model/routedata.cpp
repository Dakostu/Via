#include "routedata.h"
#include <QJsonArray>

QString RouteData::getName() const
{
    return name;
}

void RouteData::setName(const QString &value)
{
    name = value;
}

int RouteData::getSize() const
{
    return size;
}

void RouteData::setSize(int value)
{
    size = value;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setSize(size);
        }
    }
}

QColor RouteData::getColor() const
{
    return color;
}

void RouteData::setColor(const QColor &value)
{
    color = value;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setColor(color);
        }
    }
}

bool RouteData::getShowDirection() const
{
    return showDirection;
}

void RouteData::setShowDirection(bool value)
{
    showDirection = value;
}

std::list<RouteNodeData> RouteData::getNodes() const
{
    return nodes;
}

RouteData::RouteData()
{

}

RouteData::RouteData(const QJsonObject &object) {
    fromJSON(object);
}

void RouteData::fromJSON(const QJsonObject &object) {
    name = object["name"].toString();
    size = object["size"].toInt();
    color = QColor(object["color"][0].toInt(), object["color"][1].toInt(), object["color"][2].toInt());
    showDirection = object["showDirection"].toBool();

    auto nodesArray = object["nodes"].toArray();

    for (auto nodeJSON : nodesArray) {
        RouteNodeData node(nodeJSON.toObject());
        if (!node.isStyleDifferentFromRoute()) {
            node.setColor(color);
        }
        nodes.emplace_back(node);
    }

}

QJsonObject RouteData::toJSON() const {
    QJsonObject routeJSON;

    routeJSON["name"] = name;
    routeJSON["size"] = size;
    routeJSON["color"] = QJsonArray({color.red(), color.green(), color.blue()});
    routeJSON["showDirection"] = showDirection;

    QJsonArray nodesJSON;
    for (const auto &node : nodes) {
        nodesJSON << node.toJSON();
    }

    routeJSON["nodes"] = nodesJSON;

    return routeJSON;
}
