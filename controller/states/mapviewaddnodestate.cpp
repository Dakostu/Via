#include "mapviewaddnodestate.h"
#include "../../ui/mapview.h"

using namespace Via::Control;
using namespace Via::UI;

MapViewAddNodeState::MapViewAddNodeState()
{

}

void mouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    if (!mouseEvent->buttons().testFlag(Qt::RightButton)) {
        view->setDragMode(QGraphicsView::NoDrag);
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        view->setCursor(Qt::CrossCursor);
    }

    auto coords = view->mapToScene(mouseEvent->pos());
    view->getCurrentRoute()->addTemporaryPreviewNode(coords.x(), coords.y());
}

void mousePressEvent(MapView *view, QMouseEvent *mouseEvent)  {
    view->triggerParentMousePressEvent(mouseEvent);

    if (mouseEvent->buttons().testFlag(Qt::RightButton)) {
        view->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

void mouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        auto coords = view->mapToScene(mouseEvent->pos());
        view->addNodeToCurrentRoute(coords.x(), coords.y());
    } else if (mouseEvent->button() == Qt::RightButton) {
        view->setDragMode(QGraphicsView::NoDrag);
    }
}

void mouseLeaveEvent(MapView *view, QEvent *mouseEvent) {
    view->removeTemporaryNode();
}
