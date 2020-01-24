#include "uimovenodesstate.h"

#include <QCursor>

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
