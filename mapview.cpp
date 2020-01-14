#include "mapview.h"
#include <QWheelEvent>
#include <QDebug>
#include <cmath>

MapView::MapView(QWidget* parent) : QGraphicsView(parent) {}


void MapView::wheelEvent(QWheelEvent *event) {

    if (event->angleDelta().ry() == 0) {
        QGraphicsView::wheelEvent(event);
    } else {

        qDebug() << event;
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        auto factor = std::pow(2.0, event->angleDelta().ry() / 240.0);
        scale(factor, factor);
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    }


}
