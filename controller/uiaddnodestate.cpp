#include "uiaddnodestate.h"


void UIAddNodeState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(true);
    quickButtonMove->setChecked(false);
    quickButtonSelect->setChecked(false);
}


void UIAddNodeState::routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {

}

void UIAddNodeState::routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {

}

void UIAddNodeState::routeNodeMousePressEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {

}

void UIAddNodeState::routeNodeMouseReleaseEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {

}

void UIAddNodeState::mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->setDragMode(QGraphicsView::NoDrag);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setCursor(Qt::CrossCursor);
    view->getCurrentRoute()->addTemporaryPreviewNode(mouseEvent->x(), mouseEvent->y());
}
