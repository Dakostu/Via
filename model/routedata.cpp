#include "routedata.h"
#include <QJsonArray>

RouteData::RouteData()
{

}

void RouteData::fromJSON(const QJsonObject &object) {
    name = object["name"].toString();
    size = object["size"].toInt();
    color = QColor(object["color"][0].toInt(), object["color"][1].toInt(), object["color"][2].toInt());
    showDirection = object["showDirection"].toBool();

    auto nodesArray = object["nodes"].toArray();
    for (auto nodeJSON : nodesArray) {
        RouteNodeData node;
        node.fromJSON(nodeJSON.toObject());
        if (!node.isStyleDifferentFromRoute()) {
            node.setColor(color);
        }
        nodes.append(node);
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
