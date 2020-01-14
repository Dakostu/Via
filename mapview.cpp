#include "mapview.h"
#include <QWheelEvent>
#include <QDebug>
#include <cmath>
#include <QStyleOptionGraphicsItem>

MapView::MapView(QWidget* parent) : QGraphicsView(parent) {
    currentDetailLevel = QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
}


void MapView::wheelEvent(QWheelEvent *event) {
    auto verticalWheelMovement = event->angleDelta().ry();
    if (verticalWheelMovement == 0) {
        QGraphicsView::wheelEvent(event);
    } else {
        auto factor = std::pow(2.0, verticalWheelMovement / 240.0);
        auto tryingToZoomOutOfLimit = (currentDetailLevel <= DETAIL_LEVEL_MIN && (factor - 1) < 0);
        auto tryingToZoomInToLimit = (currentDetailLevel >= DETAIL_LEVEL_MAX && factor-1 >= 0);
        if (tryingToZoomOutOfLimit || tryingToZoomInToLimit) {
            return;
        }
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        scale(factor, factor);
        currentDetailLevel = QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    }
}

void MapView::dragMoveEvent(QDragMoveEvent *event) {
    qDebug() << event;
    QGraphicsView::dragMoveEvent(event);
}
