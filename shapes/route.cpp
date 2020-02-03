#include "route.h"
#include "hexagon.h"
#include "diamond.h"

Route::Route(const QColor &color, QGraphicsScene *scene, std::unique_ptr<UIState> &state)
    : routeColor(color), currentScene(scene), currentState(state)
{
}


void Route::setColors(const QColor &color) {
    routeColor = color;

    for (auto &currentNode : nodes) {
        currentNode->setColors(routeColor);
    }
}

void Route::setDefaultColors() {

    for (auto &currentNode : nodes) {
        currentNode->setDefaultColors();
    }
}

void Route::addNode(qreal x, qreal y) {
    if (nodes.back() && nodes.back()->opacity() == TEMPORARY_NODE_OPACITY) {
        currentScene->removeItem(nodes.back());
        nodes.erase(nodes[nodes.size() - 1]);
    }

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
    currentNode = *currentNodePos;

    if (index == 0) {
        nodes.front()->resetFromConnection();
    } else if (index == nodes.size()) {
        nodes.back()->resetToConnection();
    } else if (index > 0 && index < nodes.size()) {
        auto &previousNode = **nodes[index - 1];
        currentNode->connect(previousNode);
        currentScene->addItem(previousNode.getToConnection());
    }

    for (; currentNodePos != nodes.end(); ++currentNodePos) {
        (*currentNodePos)->setNodeLabelText(QString::number(index + 1));
        ++index;
    }

}

void Route::setElementSize(int newSize) {
    for (auto &currentNode : nodes) {
        currentNode->setElementSize(newSize);
    }
    ViewCustomizable::setElementSize(newSize);
}
