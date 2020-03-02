#include "../ui/localizeduistrings.h"
#include "routedata.h"
#include <QJsonArray>

using namespace Via::Interfaces;
using namespace Via::Model;
using namespace Via::Structures;
using namespace Via::UI;


RouteData::RouteData() : Data(), showOrder(DEFAULT_SHOW_ORDER)
{

}

RouteData::RouteData(const QColor &color, char newStyle) : RouteData() {
    setColors(color);
    style = newStyle;
}

RouteData::RouteData(const QJsonObject &object) : RouteData() {
    fromJSON(object);
}

void RouteData::fromJSON(const QJsonObject &object) {
    name = object[ROUTE_NAME_KEY].toString();
    elementSize = object[ROUTE_SIZE_KEY].toInt();
    currentColor = QColor(object[ROUTE_COLOR_KEY][0].toInt(), object[ROUTE_COLOR_KEY][1].toInt(), object[ROUTE_COLOR_KEY][2].toInt());
    showOrder = object[ROUTE_SHOW_ORDER_KEY].toBool();
    style = object[ROUTE_SHAPE_KEY].toInt();

    auto nodesArray = object[ROUTE_NODES_KEY].toArray();

    for (auto nodeJSON : nodesArray) {
        RouteNodeData node(nodeJSON.toObject());
        if (!node.isStyleDifferentFromRoute()) {
            node.setColors(this->currentColor);
            node.setElementSize(this->elementSize);
            node.setShapeKey(this->style);
        }
        addNode(node);
    }

    refreshNames(nodes.begin(), 0);

}

QJsonObject RouteData::toJSON() const {
    QJsonObject routeJSON;

    routeJSON[ROUTE_NAME_KEY] = name;
    routeJSON[ROUTE_SIZE_KEY] = elementSize;
    routeJSON[ROUTE_COLOR_KEY] = QJsonArray({currentColor.red(), currentColor.green(), currentColor.blue()});
    routeJSON[ROUTE_SHOW_ORDER_KEY] = showOrder;
    routeJSON[ROUTE_SHAPE_KEY] = style;

    QJsonArray nodesJSON;
    for (const auto &node : nodes) {
        nodesJSON << node.toJSON();
    }

    routeJSON[ROUTE_NODES_KEY] = nodesJSON;

    return routeJSON;
}

IndexList<RouteNodeData> RouteData::getNodes() const
{
    return nodes;
}

char RouteData::getShapeKey() const
{
    return style;
}

void RouteData::setShapeKey(char newStyle)
{
    style = newStyle;
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

void RouteData::refreshNames(RouteDataIterator&& it, int index) {
    if (it == nodes.end()) {
        return;
    }

    for (; it != nodes.end(); ++it, ++index) {
        auto &node = *it;
        QString newNumber = QString::number(index + 1);
        if (!node.isNameChangedByUser() && node.getName() != newNumber) {
            node.setName(LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(newNumber));
        }
    }
}

void RouteData::addNode(const RouteNodeData &node) {
    nodes.emplace_back(node);
}

void RouteData::eraseNode(int index) {
    auto iterator = nodes[index];
    refreshNames(nodes.erase(iterator), index);
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

void RouteData::activateColors() {
    currentColor = Qt::black;
    for (auto &node : nodes) {
        if (!node.isStyleDifferentFromRoute()) {
            node.activateColors();
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

    return (this->toJSON() == other.toJSON());
}
