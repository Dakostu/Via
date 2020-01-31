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

    auto previousNode = nodes.back();
    nodes.emplace_back(new RouteNode(new Hexagon(x,y, routeColor),
                       QString::number(nodes.size() + 1), currentState));

    nodes.back()->setElementSize(getElementSize());
    if (previousNode) {
        nodes.back()->connect(*previousNode);
        currentScene->addItem(previousNode->getToConnection());
    }
    nodes.back()->setZValue(std::numeric_limits<qreal>::max());
    currentScene->addItem(nodes.back());
}

void Route::setElementSize(int newSize) {
    for (auto &currentNode : nodes) {
        currentNode->setElementSize(newSize);
    }
    ViewCustomizable::setElementSize(newSize);
}
