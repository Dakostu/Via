#include "uiaddnodestate.h"


void UIAddNodeState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(true);
    quickButtonMove->setChecked(false);
    quickButtonSelect->setChecked(false);
}

void UIAddNodeState::mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    if (!mouseEvent->buttons().testFlag(Qt::RightButton)) {
        view->setDragMode(QGraphicsView::NoDrag);
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        view->setCursor(Qt::CrossCursor);
    }

    auto coords = view->mapToScene(mouseEvent->pos());
    view->getCurrentRoute()->addTemporaryPreviewNode(coords.x(), coords.y());
}

void UIAddNodeState::mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMousePressEvent(mouseEvent);

    if (mouseEvent->buttons().testFlag(Qt::RightButton)) {
        view->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

void UIAddNodeState::mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        auto coords = view->mapToScene(mouseEvent->pos());
        view->addNodeToCurrentRoute(coords.x(), coords.y());
    } else if (mouseEvent->button() == Qt::RightButton) {
        view->setDragMode(QGraphicsView::NoDrag);
    }
}

void UIAddNodeState::mapViewMouseLeaveEvent(MapView *view, QEvent *mouseEvent) {
    view->removeTemporaryNode();
}
