#include "mapview.h"
#include <cmath>
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QStyleOptionGraphicsItem>
#include <QWheelEvent>
#include "../shapes/octagon.h"

MapView::MapView(QWidget* parent) : QGraphicsView(parent) {
    currentDetailLevel = QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::ScrollHandDrag);   

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
    QGraphicsView::mouseMoveEvent(event);
    if (event->buttons().testFlag(Qt::LeftButton)) {
        const QRect screenRect = QApplication::desktop()->screenGeometry(this);
        auto eventPos = event->globalPos();
        auto hBar = horizontalScrollBar();
        auto vBar = verticalScrollBar();
        auto oldX = hBar->value();
        auto oldY = vBar->value();

        auto reEnterBoundaries = [](auto boundaryValue, auto firstBoundary, auto secondBoundary, QScrollBar *bar) {
            if (boundaryValue <= firstBoundary + 4 && bar->value() < bar->maximum() - 10) {
                return (secondBoundary - 5);
            } else if (boundaryValue >= secondBoundary - 4 && bar->value() > 10) {
                return (firstBoundary + 5);
            }
            return boundaryValue;
        };

        eventPos.setX(reEnterBoundaries(eventPos.x(), screenRect.left(), screenRect.right(), hBar));
        eventPos.setY(reEnterBoundaries(eventPos.y(), screenRect.top(), screenRect.bottom(), vBar));

        if (event->globalX() != eventPos.x()) {
            hBar->setValue(oldX+200);
            QCursor::setPos(eventPos);
            //hBar->setValue(oldX);
        } else if (event->globalY() != eventPos.y()) {
            vBar->setValue(oldY+200);
            QCursor::setPos(eventPos);
            //vBar->setValue(oldY);
        }
    }
}
