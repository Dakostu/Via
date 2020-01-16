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
    for (auto &currentConn : connections) {
        currentConn->setColors(routeColor);
    }
}

void Route::setDefaultColors() {

    for (auto &currentNode : nodes) {
        currentNode->setDefaultColors();
    }
    for (auto &currentConn : connections) {
        currentConn->setDefaultColors();
    }
}

void Route::addNode(qreal x, qreal y) {

    auto previousNode = nodes.back();
    nodes.emplace_back(new RouteNode(new Hexagon(x,y, routeColor),
                       QString::number(nodes.size() + 1)));

    if (previousNode) {
        nodes.back()->connect(*previousNode);
        for (const auto &connection : previousNode->getFromConnections()) {
            currentScene->addItem(connection);
        }
    }
    nodes.back()->setZValue(std::numeric_limits<qreal>::max());
    currentScene->addItem(nodes.back());
}
