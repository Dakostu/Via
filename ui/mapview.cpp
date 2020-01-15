#include "mapview.h"
#include <cmath>
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
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
    const QRect screenRect = QApplication::desktop()->screenGeometry(this);
    auto eventPos = event->globalPos();
    if (event->buttons().testFlag(Qt::LeftButton)) {

        auto reEnterBoundaries = [](auto boundaryValue, auto firstBoundary, auto secondBoundary) {
            if (boundaryValue <= firstBoundary + 4) {
                return (secondBoundary - 5);
            } else if (boundaryValue >= secondBoundary - 4) {
                return (firstBoundary + 5);
            }
            return boundaryValue;
        };

        eventPos.setX(reEnterBoundaries(eventPos.x(), screenRect.left(), screenRect.right()));
        eventPos.setY(reEnterBoundaries(eventPos.y(), screenRect.top(), screenRect.bottom()));

        QCursor::setPos(eventPos);
    }

    auto eventPos2 = mapToScene(event->localPos().x(), event->localPos().y());
    auto bla = new Octagon(eventPos2.x(),eventPos2.y(),QBrush(Qt::red),QPen(Qt::black), "1");
    this->scene()->addItem(bla);
    this->scene()->addItem(bla->getText());


    QGraphicsView::mouseMoveEvent(event);
}
