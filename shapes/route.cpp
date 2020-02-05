#include "route.h"
#include "hexagon.h"
#include "diamond.h"

Route::Route(const QColor &color, QGraphicsScene *scene, std::unique_ptr<UIState> &state)
    : routeColor(color), currentScene(scene), currentState(state)
{
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
        // shape?
    }

}

bool Route::hasTemporaryPreviewNode() {
    return nodes.back() && nodes.back()->opacity() == TEMPORARY_NODE_OPACITY;
}

void Route::removeTemporaryPreviewNode() {
    if (hasTemporaryPreviewNode()) {
        currentScene->removeItem(nodes.back());
        nodes.erase(nodes[nodes.size() - 1]);
    }
}

void Route::addNode(qreal x, qreal y) {
    removeTemporaryPreviewNode();

    auto previousNode = nodes.back();
    nodes.emplace_back(new RouteNode(new Hexagon(x,y, routeColor),
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

void Route::swapNodes(int x, int y) {
    (*nodes[x])->swap(*nodes[y]);
}

void Route::setElementSize(int newSize) {
    for (auto &currentNode : nodes) {
        currentNode->setElementSize(newSize);
    }
    ViewCustomizable::setElementSize(newSize);
}

