#include "mapview.h"
#include <cmath>
#include <QApplication>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QWheelEvent>
#include "../shapes/octagon.h"

MapView::MapView(QWidget* parent) : QGraphicsView(parent) {
    currentDetailLevel = QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::ScrollHandDrag);   

}

void MapView::setUIState(std::unique_ptr<UIState> &state) {
    currentState = &state;
}


void MapView::wheelEvent(QWheelEvent *event) {
    auto verticalWheelMovement = event->angleDelta().ry();
    if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
        QGraphicsView::wheelEvent(event);
    } else {
        auto factor = std::pow(2.0, verticalWheelMovement / 240.0);
        auto tryingToZoomOutOfLimit = (currentDetailLevel <= DETAIL_LEVEL_MIN && (factor - 1) < 0);
        auto tryingToZoomInToLimit = (currentDetailLevel >= DETAIL_LEVEL_MAX && factor-1 >= 0);

        if (tryingToZoomOutOfLimit || tryingToZoomInToLimit) {
            return;
        }

        scale(factor, factor);
        currentDetailLevel = QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
    }
}


void MapView::mouseMoveEvent(QMouseEvent* event) {
    currentState->get()->mapViewMouseMoveEvent(this, event);
}

void MapView::triggerParentMousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);
}

void MapView::triggerParentMouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
}

void MapView::addRoute() {
    drawnRoutes.emplace_back(new Route(Qt::red, this->scene(), *currentState));
    currentRoute = drawnRoutes.back().get();
}

void MapView::addNodeToCurrentRoute(int x, int y) {
    currentRoute->addNode(x,y);
}

Route *MapView::getCurrentRoute() const
{
    return currentRoute;
}
