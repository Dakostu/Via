#include "uimovenodesstate.h"

#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>
#include <QScrollBar>

void UIMoveNodesState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(false);
    quickButtonMove->setChecked(true);
    quickButtonSelect->setChecked(false);
}

void UIMoveNodesState::routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {
    auto nodeColorInverted = ~(node->getColor().rgb());
    node->setColors(nodeColorInverted);
}

void UIMoveNodesState::routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        auto thisPos = node->boundingRect().center() + node->pos();
        for (auto &conn : *node->getFromConnections()) {
            auto fromNodePos = conn->p1();
            conn->setNewPosition(fromNodePos, thisPos);
        }
        for (auto &conn : *node->getToConnections()) {
            auto toNodePos = conn->p2();
            conn->setNewPosition(thisPos, toNodePos);
        }
    }

    node->triggerParentMouseMoveEvent(mouseEvent);

}

void UIMoveNodesState::routeNodeMousePressEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {
    node->setCursor(Qt::ClosedHandCursor);
}

void UIMoveNodesState::routeNodeMouseReleaseEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {
    node->setCursor(Qt::OpenHandCursor);
}


void UIMoveNodesState::mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->triggerParentMouseMoveEvent(mouseEvent);
    if (mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        const QRect screenRect = QApplication::desktop()->screenGeometry(view);
        auto eventPos = mouseEvent->globalPos();
        auto hBar = view->horizontalScrollBar();
        auto vBar = view->verticalScrollBar();
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

        if (mouseEvent->globalX() != eventPos.x()) {
            hBar->setValue(oldX+200);
            QCursor::setPos(eventPos);
            //hBar->setValue(oldX);
        } else if (mouseEvent->globalY() != eventPos.y()) {
            vBar->setValue(oldY+200);
            QCursor::setPos(eventPos);
            //vBar->setValue(oldY);
        }
    }

}
