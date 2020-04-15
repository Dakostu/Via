#include "mapview.h"
#include <cmath>
#include <QApplication>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QWheelEvent>
#include "../shapes/octagon.h"

using namespace Via::UI;
using namespace Via::Control;
using namespace Via::Model;
using namespace Via::Shapes;

MapView::MapView(QWidget* parent) : QGraphicsView(parent), currentState{} {
    currentDetailLevel = QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::ScrollHandDrag);   

}

void MapView::setUIState(std::unique_ptr<MapViewState> &state) {
    currentState = &state;
}


void MapView::wheelEvent(QWheelEvent *event) {
    auto verticalWheelMovement = event->angleDelta().ry();
    if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
        QGraphicsView::wheelEvent(event);
    } else {
        auto zoomFactor = std::pow(2.0, verticalWheelMovement / 240.0);
        auto tryingToZoomOutOfLimit = (currentDetailLevel <= DETAIL_LEVEL_MIN && (zoomFactor - 1) < 0);
        auto tryingToZoomInToLimit = (currentDetailLevel >= DETAIL_LEVEL_MAX && zoomFactor -1 >= 0);

        if (tryingToZoomOutOfLimit || tryingToZoomInToLimit) {
            return;
        }

        scale(zoomFactor, zoomFactor);
        currentDetailLevel = QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
    }
}


void MapView::mouseMoveEvent(QMouseEvent* event) {
    currentState->get()->mouseMoveEvent(this, event);
}

void MapView::mousePressEvent(QMouseEvent *event) {
    currentState->get()->mousePressEvent(this, event);
}

void MapView::mouseReleaseEvent(QMouseEvent *event) {
    currentState->get()->mouseReleaseEvent(this, event);
}

bool MapView::viewportEvent(QEvent *event) {
    if (event->type() == QEvent::Leave) {
        currentState->get()->mouseLeaveEvent(this, event);
    }
    return QGraphicsView::viewportEvent(event);
}

void MapView::triggerParentMousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);
}

void MapView::triggerParentMouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
}

void MapView::triggerParentMouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);
}
