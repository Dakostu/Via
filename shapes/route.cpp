#include "route.h"
#include "hexagon.h"
#include "diamond.h"

Route::Route(const QColor &color, QGraphicsScene *scene)
    : routeColor(color), currentScene(scene)
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
                       QString::number(nodes.size() + 1)));

    nodes.back()->setSize(getSize());
    if (previousNode) {
        nodes.back()->connect(*previousNode);
        for (const auto &connection : *previousNode->getToConnections()) {
            currentScene->addItem(connection);
        }
    }
    nodes.back()->setZValue(std::numeric_limits<qreal>::max());
    currentScene->addItem(nodes.back());
}

void Route::setSize(qreal newSize) {
    for (auto &currentNode : nodes) {
        currentNode->setSize(newSize);
    }
    ViewCustomizable::setSize(newSize);
}
