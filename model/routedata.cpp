#include "routedata.h"
#include <QJsonArray>

RouteData::RouteData() : ViewCustomizable(), showDirection(DEFAULT_SHOW_DIR)
{

}

RouteData::RouteData(const QColor &routeColor) : ViewCustomizable() {
    setColors(routeColor);
}

RouteData::RouteData(const QJsonObject &object) : RouteData() {
    fromJSON(object);
}

void RouteData::fromJSON(const QJsonObject &object) {
    name = object["name"].toString();
    elementSize = object["nodeSize"].toDouble();
    routeColor = QColor(object["color"][0].toInt(), object["color"][1].toInt(), object["color"][2].toInt());
    showDirection = object["showDirection"].toBool();

    auto nodesArray = object["nodes"].toArray();

    for (auto nodeJSON : nodesArray) {
        RouteNodeData node(nodeJSON.toObject());
        if (!node.isStyleDifferentFromRoute()) {
            node.setColors(this->routeColor);
            node.setElementSize(this->elementSize);
        }
        addNode(node);
    }

}

QJsonObject RouteData::toJSON() const {
    QJsonObject routeJSON;

    routeJSON["name"] = name;
    routeJSON["nodeSize"] = elementSize;
    routeJSON["color"] = QJsonArray({routeColor.red(), routeColor.green(), routeColor.blue()});
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
    newNode.setColors(this->routeColor);
    newNode.setNodeName(QString::number(nodes.size() + 1));
    newNode.setElementSize(this->elementSize);
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
    auto iterator = iterateToPosition(index);
    auto newNode = generateNewNode(x,y);

    newNode.setNodeName(QString::number(index + 1));

    nodes.insert(iterator, newNode);

    refreshNames(iterator, index + 1);
}

void RouteData::refreshNames(RouteDataIterator& it, size_t index) {
    if (it == nodes.end()) {
        return;
    }

    for (; it != nodes.end(); ++it, ++index) {
        auto &node = *it;
        QString newNumber = QString::number(index + 1);
        if (!node.isNameChangedByUser() && node.getNodeName() != newNumber) {
            node.setNodeName(newNumber);
        }
    }
}

void RouteData::addNode(const RouteNodeData &node) {
    nodes.emplace_back(node);
}

void RouteData::eraseNode(size_t index) {
    auto iterator = iterateToPosition(index);

    iterator = nodes.erase(iterator);

    refreshNames(iterator, index);
}

QString RouteData::getName() const
{
    return name;
}

void RouteData::setName(const QString &value)
{
    name = value;
}


QColor RouteData::getColor() const
{
    return routeColor;
}

bool RouteData::getShowDirection() const
{
    return showDirection;
}

void RouteData::setShowDirection(bool value)
{
    showDirection = value;
}

void RouteData::setColors(const QColor &color) {
    routeColor = color;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setColors(color);
        }
    }
}

void RouteData::setDefaultColors() {
    routeColor = Qt::black;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setDefaultColors();
        }
    }
}

void RouteData::setElementSize(qreal newSize) {
    elementSize = newSize;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setElementSize(newSize);
        }
    }
}


RouteDataIterator RouteData::iterateToPosition(size_t index) {
    auto nodesSize = nodes.size();

    if (index >= nodesSize) {
        throw std::out_of_range("route node index is larger than route size");
    }

    if (index == 0) {
        return nodes.begin();
    } else if (index == nodesSize - 1) {
        return --nodes.end();
    }

    std::list<RouteNodeData>::iterator currentIterator;
    int distance;
    auto indexIsInLeftHalf = index < nodesSize/2;

    if (indexIsInLeftHalf) {
        currentIterator = ++nodes.begin();
        distance = static_cast<int>(index - 1);
    } else {
        currentIterator = nodes.end();
        distance = static_cast<int>(-nodesSize + index);
    }

    std::advance(currentIterator, distance);
    return currentIterator;
}

size_t RouteData::length() const {
    return nodes.size();
}

RouteNodeData& RouteData::operator[](size_t index) {
    return *iterateToPosition(index);
}

bool RouteData::operator==(const RouteData &other) const {
    if (this->length() != other.length()) {
        return false;
    }

    return (this->name == other.name
            && this->elementSize == other.elementSize
            && this->routeColor == other.routeColor
            && this->showDirection == other.showDirection
            && this->nodes == other.nodes);
}
