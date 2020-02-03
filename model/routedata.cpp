#include "routedata.h"
#include <QJsonArray>

RouteData::RouteData() : Data(), showOrder(DEFAULT_SHOW_ORDER)
{

}

RouteData::RouteData(const QColor &color) : RouteData() {
    setColors(color);
}

RouteData::RouteData(const QJsonObject &object) : RouteData() {
    fromJSON(object);
}

void RouteData::fromJSON(const QJsonObject &object) {
    name = object["name"].toString();
    elementSize = object["nodeSize"].toInt();
    currentColor = QColor(object["color"][0].toInt(), object["color"][1].toInt(), object["color"][2].toInt());
    showOrder = object["showOrder"].toBool();

    auto nodesArray = object["nodes"].toArray();

    for (auto nodeJSON : nodesArray) {
        RouteNodeData node(nodeJSON.toObject());
        if (!node.isStyleDifferentFromRoute()) {
            node.setColors(this->currentColor);
            node.setElementSize(this->elementSize);
        }
        addNode(node);
    }

}

QJsonObject RouteData::toJSON() const {
    QJsonObject routeJSON;

    routeJSON["name"] = name;
    routeJSON["nodeSize"] = elementSize;
    routeJSON["color"] = QJsonArray({currentColor.red(), currentColor.green(), currentColor.blue()});
    routeJSON["showOrder"] = showOrder;

    QJsonArray nodesJSON;
    for (const auto &node : nodes) {
        nodesJSON << node.toJSON();
    }

    routeJSON["nodes"] = nodesJSON;

    return routeJSON;
}

IndexList<RouteNodeData> RouteData::getNodes() const
{
    return nodes;
}

RouteNodeData RouteData::generateNewNode(int x, int y) {
    RouteNodeData newNode;
    newNode.setX(x);
    newNode.setY(y);
    newNode.setColors(this->currentColor);
    newNode.setName(QString::number(nodes.size() + 1));
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

QStringList RouteData::getNodeTitles() {
    QStringList nodeTitleList;

    for (const auto &node : nodes) {
        nodeTitleList << node.getName();
    }
    return nodeTitleList;
}

void RouteData::addNode(int x, int y) {
    nodes.emplace_back(generateNewNode(x,y));
}

void RouteData::addNode(int x, int y, size_t index) {
    auto iterator = nodes[index];
    auto newNode = generateNewNode(x,y);

    newNode.setName(QString::number(index + 1));

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
        if (!node.isNameChangedByUser() && node.getName() != newNumber) {
            node.setName(newNumber);
        }
    }
}

void RouteData::addNode(const RouteNodeData &node) {
    nodes.emplace_back(node);
}

void RouteData::eraseNode(size_t index) {
    auto iterator = nodes[index];

    iterator = nodes.erase(iterator);

    refreshNames(iterator, index);
}

bool RouteData::getShowOrder() const
{
    return showOrder;
}

void RouteData::setShowOrder(bool value)
{
    showOrder = value;
}

void RouteData::setColors(const QColor &color) {
    currentColor = color;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setColors(color);
        }
    }
}

void RouteData::setDefaultColors() {
    currentColor = Qt::black;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setDefaultColors();
        }
    }
}

void RouteData::setElementSize(int newSize) {
    elementSize = newSize;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.setElementSize(newSize);
        }
    }
}

size_t RouteData::length() const {
    return nodes.size();
}

RouteNodeData& RouteData::operator[](int index) {
    return *nodes[index];
}

bool RouteData::operator==(const RouteData &other) const {
    if (this->length() != other.length()) {
        return false;
    }

    return (this->name == other.name
            && this->elementSize == other.elementSize
            && this->currentColor == other.currentColor
            && this->showOrder == other.showOrder
            && this->nodes == other.nodes);
}
