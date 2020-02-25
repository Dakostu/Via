#include "route.h"
#include "hexagon.h"
#include "diamond.h"
#include "square.h"

using namespace Via::Shapes;
using namespace Via::Control;
using namespace Via::Model;

Route::Route(const QColor &color, const QString &selectedStyle, QGraphicsScene *scene, std::unique_ptr<RouteNodeState> &state)
    : routeColor(color), style(selectedStyle), currentScene(scene), currentState(state)
{
}

QString Route::getStyle() const
{
    return style;
}

void Route::setStyle(const QString &value)
{
    style = value;
    for (auto &node : nodes) {
        if (!node->getStyleDiffersFromRoute()) {
            node->removeFromGroup(node->getNodeShape());
            auto newShape = nodeShapeFactory.generateNodeShape(style, node->getCenter().x(), node->getCenter().y(), routeColor);
            node->setShape(newShape);
            node->addToGroup(newShape);
        }
    }
}

QColor Route::getColors() const {
    return routeColor;
}

void Route::setColors(const QColor &color) {
    routeColor = color;    

    for (auto &currentNode : nodes) {
        currentNode->setColors(routeColor);
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
        newNode->setShape(nodeShapeFactory.generateNodeShape(node.getStyle(), node.getX(), node.getY(), node.getColor()));
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
        nodes.erase(nodes[nodes.size() - 1]);
    }
}

void Route::addNode(qreal x, qreal y) {
    removeTemporaryPreviewNode();

    auto previousNode = nodes.back();
    nodes.emplace_back(new RouteNode(nodeShapeFactory.generateNodeShape(style, x, y, routeColor),
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
        currentNode->connect(previousNode);
        currentScene->addItem(previousNode.getToConnection());
        currentNode->updateRouteConnections();
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

void Route::swapNodes(int node1, int node2) {
    (*nodes[node1])->swap(*nodes[node2]);
}

void Route::setElementSize(int newSize) {
    for (auto &currentNode : nodes) {
        currentNode->setElementSize(newSize);
    }
    ViewCustomizable::setElementSize(newSize);
}

