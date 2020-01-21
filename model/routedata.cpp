#include "routedata.h"
#include <QJsonArray>
#include <variant>

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


void RouteData::addNode(const RouteNodeData node) {
    nodes.emplace_back(node);
}

RouteNodeData& RouteData::operator[](size_t index) {
    auto nodesSize = nodes.size();

    if (index >= nodesSize) {
        throw std::out_of_range("route node index is larger than route size");
    }

    if (index == 0) {
        return nodes.front();
    } else if (index == nodesSize - 1) {
        return nodes.back();
    }

    std::variant<std::list<RouteNodeData>::iterator, std::list<RouteNodeData>::reverse_iterator> begin;
    std::variant<std::list<RouteNodeData>::iterator, std::list<RouteNodeData>::reverse_iterator> end;
    std::function<void(size_t&)> moveIndex;
    size_t currentIndex;
    auto indexIsInLeftHalf = index < nodesSize/2;

    if (indexIsInLeftHalf) {
        begin = ++nodes.begin();
        currentIndex = 1;
        moveIndex = [](size_t& index) {++index;};
    } else {
        begin = ++nodes.rbegin();
        currentIndex = nodesSize - 2;
        moveIndex = [](size_t& index) {--index;};
    }

    while (currentIndex != index) {
        std::visit([](auto &&iterator){++iterator;}, begin);
        moveIndex(currentIndex);
    }

    if (auto val = std::get_if<std::list<RouteNodeData>::iterator>(&begin)) {
        return **val;
    } else {
        return *(std::get<std::list<RouteNodeData>::reverse_iterator>(begin));
    }


}
