#include "route.h"
#include "hexagon.h"
#include "diamond.h"
#include "square.h"

using namespace Via::Shapes;
using namespace Via::Control;
using namespace Via::Model;

Route::Route(const QColor &color, char selectedStyle, QGraphicsScene *scene, std::unique_ptr<RouteNodeState> &state)
    : showDirection(true), routeColor(color), style(selectedStyle), currentScene(scene), currentState(state)
{
}

Route::Route(const QColor &color, const QString &selectedStyle, QGraphicsScene *scene, std::unique_ptr<RouteNodeState> &state)
    : Route(color, ' ', scene, state)
{
    setShapeKey(selectedStyle);
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

    for (auto i = 0; i < nodes.size(); ++i) {
        if (!(*nodes[i])->getStyleDiffersFromRoute()) {
            setStyleOfNode(i, this->style);
        }
    }
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

void Route::addNode(const RouteNodeData &node) {
    addNode(node.getX(), node.getY());

    auto newNode = nodes.back();

    if (node.isStyleDifferentFromRoute()) {
        newNode->setColors(node.getColor());
        newNode->setElementSize(node.getElementSize());        
        newNode->setShape(nodeShapeFactory.generateNodeShape(node.getShapeKey(), node.getCenter(), node.getColor()));
        newNode->setStyleDiffersFromRoute(true);
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

void Route::eraseNode(int index) {
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

void Route::connectNodes(RouteNode &from, RouteNode &to) {
    to.connect(from);
    currentScene->addItem(from.getToConnection());
    to.updateRouteConnections();
    if (to.getStyleDiffersFromRoute()) {
        from.setToConnectionColor(routeColor);
    }
}

void Route::swapConnections(int firstNodeIndex, int secondNodeIndex) {
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

void Route::swapNodes(int firstNodeIndex, int secondNodeIndex) {
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


void Route::setStyleOfNode(int routeNodeIndex, const QString &newStyle) {
    setStyleOfNode(routeNodeIndex, nodeShapeFactory.getShapeKeyFromUIString(newStyle));
}

void Route::setStyleOfNode(int routeNodeIndex, char newStyle) {
    auto selectedNode = *nodes[routeNodeIndex];
    auto newShape = nodeShapeFactory.generateNodeShape(newStyle, selectedNode->getCenter(), selectedNode->getColors());
    selectedNode->setShape(newShape);
    selectedNode->checkIfStyleIsDifferent(this->style, this->getColors(), this->elementSize);
}

void Route::setColorsOfNode(int routeNodeIndex, const QColor &newColor) {
    auto selectedNode = *nodes[routeNodeIndex];
    selectedNode->setColors(newColor);
    selectedNode->checkIfStyleIsDifferent(this->style, this->getColors(), this->elementSize);
}

const RouteNode& Route::operator[](int nodeIndex) {
    return *(*nodes[nodeIndex]);
}
