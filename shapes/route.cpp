#include "../model/routedata.h"
#include "../model/routenodedata.h"
#include "route.h"
#include "hexagon.h"
#include "diamond.h"
#include "square.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Via::Shapes;
using namespace Via::Control;
using namespace Via::Model;

Route::Route(const QColor &color, char selectedStyle, QGraphicsScene *scene, std::unique_ptr<RouteNodeState> &state)
    : showOrder(true), routeColor(color), style(selectedStyle), currentScene(scene), currentState(state)
{
}

Route::Route(const QColor &color, const QString &selectedStyle, QGraphicsScene *scene, std::unique_ptr<RouteNodeState> &state)
    : Route(color, ' ', scene, state)
{
    setShapeKey(selectedStyle);
}

Route::Route(const QJsonObject &object, QGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state)
    : currentScene(scene), currentState(state) {
    fromJSON(object);
}

char Route::getShapeKey() const
{
    return style;
}


void Route::setShapeKey(const QString &newStyle) {
    setShapeKey(nodeShapeFactory.getShapeKeyFromUIString(newStyle));
}

void Route::setShapeKey(char newStyle)
{
    style = newStyle;

    for (size_t i = 0; i < nodes.size(); ++i) {
        if (!(*nodes[i])->getStyleDiffersFromRoute()) {
            setStyleOfNode(i, this->style);
        }
    }
}

void Route::fromJSON(const QJsonObject &object) {

    name = object[RouteData::ROUTE_NAME_KEY].toString();
    elementSize = object[RouteData::ROUTE_SIZE_KEY].toInt();
    setColors(QColor(object[RouteData::ROUTE_COLOR_KEY][0].toInt(),
            object[RouteData::ROUTE_COLOR_KEY][1].toInt(),
            object[RouteData::ROUTE_COLOR_KEY][2].toInt()));
    showOrder = object[RouteData::ROUTE_SHOW_ORDER_KEY].toBool();
    style = static_cast<char>(object[RouteData::ROUTE_SHAPE_KEY].toInt());

    auto nodesArray = object[RouteData::ROUTE_NODES_KEY].toArray();

    for (const auto nodeJSONRef : nodesArray) {

        auto nodeJSONObject = nodeJSONRef.toObject();

        auto nodeX = nodeJSONObject[RouteNodeData::NODE_X_KEY].toInt();
        auto nodeY = nodeJSONObject[RouteNodeData::NODE_Y_KEY].toInt();

        addNode(nodeX, nodeY);

        auto newNode = nodes.back();
        newNode->fromJSON(nodeJSONObject);

        if (newNode->getStyleDiffersFromRoute()) {
            auto shapeKey = nodeJSONObject[RouteNodeData::NODE_SHAPE_KEY].toInt();
            newNode->setShape(nodeShapeFactory.generateNodeShape(static_cast<char>(shapeKey), newNode->getCenter(), newNode->getColors()));
        }
    }

    //refreshNames(nodes.begin(), 0);

}

QJsonObject Route::toJSON() {
    QJsonObject routeJSON;

    auto currentColor = getColors();
    routeJSON[RouteData::ROUTE_NAME_KEY] = name;
    routeJSON[RouteData::ROUTE_SIZE_KEY] = elementSize;
    routeJSON[RouteData::ROUTE_COLOR_KEY] = QJsonArray({currentColor.red(), currentColor.green(), currentColor.blue()});
    routeJSON[RouteData::ROUTE_SHOW_ORDER_KEY] = showOrder;
    routeJSON[RouteData::ROUTE_SHAPE_KEY] = style;

    QJsonArray nodesJSON;
    for (const auto &node : nodes) {
        nodesJSON << node->toJSON();
    }

    routeJSON[RouteData::ROUTE_NODES_KEY] = nodesJSON;

    return routeJSON;
}

QColor Route::getColors() const {
    return routeColor;
}

void Route::setColors(const QColor &color) {
    routeColor = color;    

    for (auto &currentNode : nodes) {
        if (!currentNode->getStyleDiffersFromRoute()) {
            currentNode->setColors(routeColor);
        }
        currentNode->setToConnectionColor(routeColor);
    }
}

void Route::activateColors() {
    for (auto &currentNode : nodes) {
        currentNode->activateColors();
    }
}

bool Route::hasTemporaryPreviewNode() {
    return nodes.back() && nodes.back()->opacity() <= TEMPORARY_NODE_OPACITY;
}

void Route::removeTemporaryPreviewNode() {
    if (hasTemporaryPreviewNode()) {
        auto tempNode = nodes.back();
        currentScene->removeItem(tempNode->getFromConnection());
        currentScene->removeItem(tempNode);
        nodes.pop_back();
    }
}

void Route::addNode(qreal x, qreal y) {
    removeTemporaryPreviewNode();

    auto previousNode = nodes.back();
    nodes.emplace_back(new RouteNode(nodeShapeFactory.generateNodeShape(style, {x, y}, routeColor),
                       QString::number(nodes.size() + 1), currentState));

    nodes.back()->setElementSize(getElementSize());    
    if (previousNode) {
        nodes.back()->connect(*previousNode);
        currentScene->addItem(previousNode->getToConnection());
    }
    currentScene->addItem(nodes.back());
}

void Route::addTemporaryPreviewNode(qreal x, qreal y) {
    addNode(x, y);
    auto tempNode = nodes.back();
    if (tempNode->getFromConnection()) {
        tempNode->getFromConnection()->setOpacity(TEMPORARY_NODE_OPACITY);
    }
    tempNode->setOpacity(TEMPORARY_NODE_OPACITY);
}

void Route::eraseNode(size_t index) {
    auto currentNodePos = nodes[index];
    auto currentNode = *currentNodePos;
    currentScene->removeItem(currentNode->getFromConnection());
    currentScene->removeItem(currentNode->getToConnection());
    currentScene->removeItem(currentNode);

    currentNodePos = nodes.erase(currentNodePos);

    if (nodes.empty()) {
        return;
    }

    currentNode = *currentNodePos;

    if (index == 0) {
        nodes.front()->resetFromConnection();
    } else if (index == nodes.size()) {
        nodes.back()->resetToConnection();
    } else if (index > 0 && index < nodes.size()) {
        auto &previousNode = **nodes[index - 1];
        connectNodes(previousNode, *currentNode);
    }

    for (; currentNodePos != nodes.end(); ++currentNodePos) {
        (*currentNodePos)->setNodeLabelText(QString::number(index + 1));
        ++index;
    }
}

void Route::eraseAllNodes() {
    while (!nodes.empty()) {
        eraseNode(0);
    }
}

Via::Structures::IndexList<RouteNode*>& Route::getNodes()
{
    return nodes;
}

void Route::setCurrentScene(QGraphicsScene *value)
{
    currentScene = value;
}

void Route::setCurrentState(std::unique_ptr<Via::Control::RouteNodeState> &value)
{
    currentState.swap(value);
}

bool Route::getShowOrder() const
{
    return showOrder;
}

void Route::setShowOrder(bool value)
{
    showOrder = value;
}

void Route::connectNodes(RouteNode &from, RouteNode &to) {
    to.connect(from);
    currentScene->addItem(from.getToConnection());
    to.updateRouteConnections();
    if (to.getStyleDiffersFromRoute()) {
        from.setToConnectionColor(routeColor);
    }
}

void Route::swapConnections(size_t firstNodeIndex, size_t secondNodeIndex) {
    nodes.splice(nodes[firstNodeIndex], nodes, nodes[secondNodeIndex]);

    auto &firstNode = **nodes[firstNodeIndex];
    auto &secondNode = **nodes[secondNodeIndex];

    connectNodes(firstNode, secondNode);

    if (firstNodeIndex > 0) {
        auto &previousNode = **nodes[firstNodeIndex - 1];
        connectNodes(previousNode, firstNode);
    }
    if (secondNodeIndex < nodes.size() - 1) {
        auto &nextNode = **nodes[secondNodeIndex + 1];
        connectNodes(secondNode, nextNode);
    }
}

void Route::swapNodes(size_t firstNodeIndex, size_t secondNodeIndex) {
    auto &fromNode = *nodes[firstNodeIndex];
    auto &withNode = *nodes[secondNodeIndex];

    auto tempNodeLabel = withNode->getNodeLabel()->text();
    auto tempCenter = withNode->getCenter();
    //auto tempExtraLabelText = withNode->getExtraText()->text();

    auto fromNodeCenter = fromNode->getCenter();
    auto withNodeCenter = withNode->getCenter();

    withNode->moveBy(fromNodeCenter.x() - withNodeCenter.x(), fromNodeCenter.y() - withNodeCenter.y());
    withNode->getNodeLabel()->setText(fromNode->getNodeLabel()->text());

    fromNode->moveBy(tempCenter.x() - fromNodeCenter.x(), tempCenter.y() - fromNodeCenter.y());
    fromNode->getNodeLabel()->setText(tempNodeLabel);

    withNode->resetConnections();
    fromNode->resetConnections();

    if (firstNodeIndex < secondNodeIndex) {
        swapConnections(firstNodeIndex, secondNodeIndex);
    } else {
        swapConnections(secondNodeIndex, firstNodeIndex);
    }

}

void Route::setElementSize(int newSize) {
    for (auto &currentNode : nodes) {
        currentNode->setElementSize(newSize);
    }
    ViewCustomizable::setElementSize(newSize);
}


void Route::setStyleOfNode(size_t routeNodeIndex, const QString &newStyle) {
    setStyleOfNode(routeNodeIndex, nodeShapeFactory.getShapeKeyFromUIString(newStyle));
}

void Route::setStyleOfNode(size_t routeNodeIndex, char newStyle) {
    auto selectedNode = *nodes[routeNodeIndex];
    auto newShape = nodeShapeFactory.generateNodeShape(newStyle, selectedNode->getCenter(), selectedNode->getColors());
    selectedNode->setShape(newShape);
    selectedNode->checkIfStyleIsDifferent(this->style, this->getColors(), this->elementSize);
}

void Route::setColorsOfNode(size_t routeNodeIndex, const QColor &newColor) {
    auto selectedNode = *nodes[routeNodeIndex];
    selectedNode->setColors(newColor);
    selectedNode->checkIfStyleIsDifferent(this->style, this->getColors(), this->elementSize);
}

size_t Route::size() {
    return nodes.size();
}

RouteNode& Route::operator[](size_t nodeIndex) {
    return *(*nodes[nodeIndex]);
}
