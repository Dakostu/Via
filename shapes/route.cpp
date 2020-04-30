#include "../model/routedata.h"
#include "../model/routenodedata.h"

#include "../l10n/localizeduistrings.h"

#include "route.h"
#include "hexagon.h"
#include "diamond.h"
#include "square.h"
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

using namespace Via::Control;
using namespace Via::L10n;
using namespace Via::Model;
using namespace Via::Shapes;
using namespace Via::UI;

Route::Route(const QColor &color, char selectedStyle, AutomaticallyShrinkingGraphicsScene *scene, std::unique_ptr<RouteNodeState> &state)
    : showOrder(true), routeColor(color), currentScene(scene), currentState(state)
{
    setShapeKey(selectedStyle);
}

Route::Route(const QColor &color, const QString &selectedStyle, AutomaticallyShrinkingGraphicsScene *scene, std::unique_ptr<RouteNodeState> &state)
    : Route(color, ' ', scene, state)
{
    setShapeKey(selectedStyle);
}

Route::Route(const QJsonObject &object, AutomaticallyShrinkingGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state)
    : currentScene(scene), currentState(state) {
    fromJSON(object);
}

Route::~Route() {
    eraseAllNodes();
}

void Route::setShapeKey(const QString &newStyle) {
    setShapeKey(nodeShapeFactory.getShapeKeyFromUIString(newStyle));
}

void Route::setShapeKey(char newStyle)
{
    ShapeKeyModifiable::setShapeKey(newStyle);

    for (size_t i = 0; i < nodes.size(); ++i) {
        if (!(*nodes[i])->getStyleDiffersFromRoute()) {
            setStyleOfNode(i, this->shapeKey);
        }
    }
}

void Route::fromJSON(const QJsonObject &object) {

    setName(object[RouteData::ROUTE_NAME_KEY].toString());
    setNameChangedByUser(object[RouteData::ROUTE_NAME_CHANGED_KEY].toBool());
    setElementSize(object[RouteData::ROUTE_SIZE_KEY].toInt());
    setColors(QColor(object[RouteData::ROUTE_COLOR_KEY][0].toInt(),
            object[RouteData::ROUTE_COLOR_KEY][1].toInt(),
            object[RouteData::ROUTE_COLOR_KEY][2].toInt()));
    setShowOrder(object[RouteData::ROUTE_SHOW_ORDER_KEY].toBool());
    shapeKey = static_cast<char>(object[RouteData::ROUTE_SHAPE_KEY].toInt());

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

        setVisibilityOfNode(nodes.size() - 1, newNode->isCurrentlyVisible());
    }

    setVisible(object[RouteData::ROUTE_VISIBLE_KEY].toBool());
}

QJsonObject Route::toJSON() {
    QJsonObject routeJSON;

    auto currentColor = getColors();
    routeJSON[RouteData::ROUTE_NAME_KEY] = name;
    routeJSON[RouteData::ROUTE_NAME_CHANGED_KEY] = nameChangedByUser;
    routeJSON[RouteData::ROUTE_SIZE_KEY] = elementSize;
    routeJSON[RouteData::ROUTE_COLOR_KEY] = QJsonArray({currentColor.red(), currentColor.green(), currentColor.blue()});
    routeJSON[RouteData::ROUTE_SHOW_ORDER_KEY] = showOrder;
    routeJSON[RouteData::ROUTE_SHAPE_KEY] = shapeKey;
    routeJSON[RouteData::ROUTE_VISIBLE_KEY] = visible;

    QJsonArray nodesJSON;
    for (const auto &node : nodes) {
        nodesJSON << node->toJSON();
    }

    routeJSON[RouteData::ROUTE_NODES_KEY] = nodesJSON;

    return routeJSON;
}

void Route::setVisible(bool isVisible) {
    VisibilityChangeable::setVisible(isVisible);

    std::function<qreal(RouteNode&)> routeNoteVisibilityValue;

    if (isVisible) {
        routeNoteVisibilityValue = [](auto &node) { return node.isCurrentlyVisible(); };
    } else {
        routeNoteVisibilityValue = [](auto &node) { return 0.0; };
    }

    for (auto &node : nodes) {
        node->setOpacity(routeNoteVisibilityValue(*node));
    }
}

QColor Route::getColors() {
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
    auto lastNode = nodes.back();
    return lastNode && 0.0 < lastNode->opacity() && lastNode->opacity() <= TEMPORARY_NODE_OPACITY;
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

    auto previousNode = getLastVisibleRouteNode();
    auto newNodeLabel = (previousNode) ? QString::number(previousNode->getNodeLabel()->text().toInt() + 1)
                                       : QString("1");

    nodes.emplace_back(new RouteNode(nodeShapeFactory.generateNodeShape(shapeKey, {x, y}, routeColor),
                       newNodeLabel, currentState));

    auto newNode = nodes.back();
    newNode->setElementSize(getElementSize());
    newNode->setNodeLabelOpacity(showOrder);
    if (previousNode) {
        newNode->connect(*previousNode);
        currentScene->addItem(previousNode->getToConnection());
    }
    currentScene->addItem(newNode);
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

    refreshNodeLabels(index);

    qDebug() << currentScene->sceneRect();
}

void Route::eraseAllNodes() {
    nodes.clear();
}

size_t Route::getNodeAmount() {
    return nodes.size();
}

Via::Structures::IndexList<RouteNode*>& Route::getNodes()
{
    return nodes;
}

void Route::setCurrentScene(AutomaticallyShrinkingGraphicsScene *value)
{
    currentScene = value;
}

void Route::setCurrentState(std::unique_ptr<Via::Control::RouteNodeState> &value)
{
    currentState.swap(value);
}

void Route::setVisibilityOfNode(size_t routeNodeIndex, bool isVisible) {
    auto &currentNode = **nodes[routeNodeIndex];
    currentNode.setVisible(isVisible);

    auto previousVisibleNode = getPreviousVisibleRouteNode(routeNodeIndex);
    auto nextVisibleNode = getNextVisibleRouteNode(routeNodeIndex);

    auto nodeIsBetweenBeginningAndEnd = 0 < routeNodeIndex && routeNodeIndex < nodes.size() - 1;

    auto refreshNodeOpacityAccordingToRouteVisibility = [&](auto *node) {
        node->setOpacity(this->isCurrentlyVisible() && node->isCurrentlyVisible());
    };

    if (isVisible) {
        if (nodeIsBetweenBeginningAndEnd) {
            if (previousVisibleNode) {                
                connectNodes(*previousVisibleNode, currentNode);
                refreshNodeOpacityAccordingToRouteVisibility(previousVisibleNode);
            }
            if (nextVisibleNode) {
                connectNodes(currentNode, *nextVisibleNode);
                refreshNodeOpacityAccordingToRouteVisibility(nextVisibleNode);
            }
        } else if (nextVisibleNode) {
            connectNodes(currentNode, *nextVisibleNode);
            refreshNodeOpacityAccordingToRouteVisibility(nextVisibleNode);
        } else if (previousVisibleNode) {
            connectNodes(*previousVisibleNode, currentNode);
            refreshNodeOpacityAccordingToRouteVisibility(previousVisibleNode);
        }
    } else {
        currentNode.resetConnections();

        if (nodeIsBetweenBeginningAndEnd && previousVisibleNode && nextVisibleNode) {
            connectNodes(*previousVisibleNode, *nextVisibleNode);
            refreshNodeOpacityAccordingToRouteVisibility(previousVisibleNode);
            refreshNodeOpacityAccordingToRouteVisibility(nextVisibleNode);
        } else if (nextVisibleNode) {
            nextVisibleNode->resetFromConnection();
        } else if (previousVisibleNode) {
            previousVisibleNode->resetToConnection();
        }
    }

    currentNode.setOpacity(this->isCurrentlyVisible() && currentNode.isCurrentlyVisible());
    refreshNodeLabels();
}

bool Route::getShowOrder() const
{
    return showOrder;
}

void Route::setShowOrder(bool value)
{
    showOrder = value;

    for (auto &node : nodes) {
        node->setNodeLabelOpacity(value);
    }
}

QString Route::getRouteStyleAsUIString() {
    return nodeShapeFactory.getUIStringFromShapeKey(this->getShapeKey());
}

QString Route::getRouteNodeStyleAsUIString(size_t nodeIndex) {
    return nodeShapeFactory.getUIStringFromShapeKey((*nodes[nodeIndex])->getShapeKey());
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

    auto firstNode = *nodes[firstNodeIndex];
    auto secondNode = *nodes[secondNodeIndex];

    if (firstNodeIndex > 0 && !firstNode->isCurrentlyVisible()) {
        firstNodeIndex = getIndexOfPreviousVisibileRouteNode(firstNodeIndex);
        if (firstNodeIndex != std::numeric_limits<size_t>::max()) {
            firstNode = *nodes[firstNodeIndex];
        }
    }

    if (secondNodeIndex < nodes.size() && !secondNode->isCurrentlyVisible()) {
        secondNodeIndex = getIndexOfNextVisibileRouteNode(secondNodeIndex);
        if (secondNodeIndex != std::numeric_limits<size_t>::max()) {
            secondNode = *nodes[secondNodeIndex];
        }
    }

    if (firstNodeIndex > 0) {
        firstNodeIndex = getIndexOfPreviousVisibileRouteNode(firstNodeIndex);
        if (firstNodeIndex != std::numeric_limits<size_t>::max()) {
            connectNodes(**nodes[firstNodeIndex], *firstNode);
        }
    }

    if (secondNodeIndex < nodes.size() - 1) {
        secondNodeIndex = getIndexOfNextVisibileRouteNode(secondNodeIndex);
        if (secondNodeIndex != std::numeric_limits<size_t>::max()) {
            connectNodes(*secondNode, **nodes[secondNodeIndex]);
        }
    }

    if (firstNode->isCurrentlyVisible() && secondNode->isCurrentlyVisible()) {
        connectNodes(*firstNode, *secondNode);
    }
}

void Route::refreshNodeLabels(size_t index) {    
    for (auto labelText = index + 1; index < nodes.size(); ++index) {
        if ((*nodes[index])->isCurrentlyVisible()) {
            (*nodes[index])->setNodeLabelText(QString::number(labelText++));
        }
    }
}

RouteNode* Route::getLastVisibleRouteNode() {
    for (auto reverseIt = nodes.rbegin(); reverseIt != nodes.rend(); ++reverseIt) {
        if ((*reverseIt)->isCurrentlyVisible()) {
            return *reverseIt;
        }
    }

    return nullptr;
}

RouteNode* Route::getPreviousVisibleRouteNode(size_t index) {
    for (auto previousNodeIndex = index - 1; previousNodeIndex != std::numeric_limits<size_t>::max(); --previousNodeIndex) {
        if ((*nodes[previousNodeIndex])->isCurrentlyVisible()) {
            return (*nodes[previousNodeIndex]);
        }
    }

    return nullptr;
}

RouteNode* Route::getNextVisibleRouteNode(size_t index) {
    auto nextNodeIndex = index + 1;

    if (nextNodeIndex == 0 || nextNodeIndex >= nodes.size()) {
        return nullptr;
    }

    for (auto it = nodes[nextNodeIndex]; it != nodes.end(); ++it) {
        if ((*it)->isCurrentlyVisible()) {
            return *it;
        }
    }

    return nullptr;
}

size_t Route::getIndexOfPreviousVisibileRouteNode(size_t currentRouteNodeIndex) {
    for (size_t i = currentRouteNodeIndex - 1; i != std::numeric_limits<size_t>::max(); --i) {
        if ((*nodes[i])->isCurrentlyVisible()) {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}

size_t Route::getIndexOfNextVisibileRouteNode(size_t currentRouteNodeIndex) {
    for (size_t i = currentRouteNodeIndex + 1; i < nodes.size(); ++i) {
        if ((*nodes[i])->isCurrentlyVisible()) {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}

void Route::swapNodes(size_t firstNodeIndex, size_t secondNodeIndex) {
    auto &fromNode = *nodes[firstNodeIndex];
    auto &withNode = *nodes[secondNodeIndex];

    auto fromNodeCenter = fromNode->getCenter();
    auto withNodeCenter = withNode->getCenter();

    withNode->moveBy(fromNodeCenter.x() - withNodeCenter.x(), fromNodeCenter.y() - withNodeCenter.y());
    fromNode->moveBy(withNodeCenter.x() - fromNodeCenter.x(), withNodeCenter.y() - fromNodeCenter.y());

    withNode->resetConnections();
    fromNode->resetConnections();

    auto index = std::max(firstNodeIndex, secondNodeIndex);
    auto nodeDefaultNamePlusOne = QString(LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(index + 1));
    auto nodeDefaultName = QString(LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(index));

    if (firstNodeIndex < secondNodeIndex) {
        swapConnections(firstNodeIndex, secondNodeIndex);
        withNode->swapNamesConsideringDefaultNamesWith(fromNode, nodeDefaultName, nodeDefaultNamePlusOne);
    } else {
        swapConnections(secondNodeIndex, firstNodeIndex);
        fromNode->swapNamesConsideringDefaultNamesWith(withNode, nodeDefaultName, nodeDefaultNamePlusOne);
    }

    refreshNodeLabels();

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
    selectedNode->checkIfStyleIsDifferent(this->shapeKey, this->getColors(), this->elementSize);
}

void Route::setColorsOfNode(size_t routeNodeIndex, const QColor &newColor) {
    auto selectedNode = *nodes[routeNodeIndex];
    selectedNode->setColors(newColor);
    selectedNode->checkIfStyleIsDifferent(this->shapeKey, this->getColors(), this->elementSize);
}

size_t Route::size() {
    return nodes.size();
}

RouteNode& Route::operator[](size_t nodeIndex) {
    return *(*nodes[nodeIndex]);
}
