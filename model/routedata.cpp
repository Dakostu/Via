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
        addNode(node);
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

RouteNodeData RouteData::generateNewNode(int x, int y) {
    RouteNodeData newNode;
    newNode.setX(x);
    newNode.setY(y);
    newNode.setColor(this->color);
    newNode.setNodeName(QString::number(nodes.size()));
    newNode.setSize(this->size);
    newNode.setInvisible(false);
    newNode.setDifferentStyleFromRoute(false);
    newNode.setNodeLabel("");
    return newNode;
}

RouteNodeData& RouteData::getFirstNode() {
    return nodes.front();
}

RouteNodeData& RouteData::getLastNode() {
    return nodes.back();
}

void RouteData::addNode(int x, int y) {
    nodes.emplace_back(generateNewNode(x,y));
}

void RouteData::addNode(int x, int y, size_t index) {
    nodes.insert(iterateToPosition(index), generateNewNode(x,y));
}

std::list<RouteNodeData>::iterator RouteData::iterateToPosition(size_t index) {
    auto nodesSize = nodes.size();

    if (index >= nodesSize) {
        throw std::out_of_range("route node index is larger than route size");
    }

    if (index == 0) {
        return nodes.begin();
    } else if (index == nodesSize - 1) {
        return nodes.end();
    }

    std::list<RouteNodeData>::iterator currentIterator;
    int distance;
    auto indexIsInLeftHalf = index < nodesSize/2;

    if (indexIsInLeftHalf) {
        currentIterator = ++nodes.begin();
        distance = static_cast<int>(index - 2);
    } else {
        currentIterator = --nodes.end();
        --currentIterator;
        distance = static_cast<int>(-nodesSize + index + 1);
    }

    std::advance(currentIterator, distance);
    return currentIterator;
}

RouteNodeData& RouteData::operator[](size_t index) {
    return *iterateToPosition(index);
}
