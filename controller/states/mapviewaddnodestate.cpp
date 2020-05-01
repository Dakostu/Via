#include "mapviewaddnodestate.h"
#include "../../ui/mapview.h"

#include <QDebug>
#include <QScrollBar>

using namespace Via::Control;
using namespace Via::UI;

void MapViewAddNodeState::mouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    if (!mouseEvent->buttons().testFlag(Qt::RightButton)) {
        view->setDragMode(QGraphicsView::NoDrag);
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        view->setCursor(Qt::CrossCursor);
    }

    auto viewCoords = mouseEvent->pos();

    auto hBar = view->horizontalScrollBar();
    auto vBar = view->verticalScrollBar();

    if (view->mouseTouchesTopBorder(viewCoords)) {
        vBar->setValue(vBar->value() - 10);
    } else if (view->mouseTouchesBottomBorder(viewCoords)) {
        vBar->setValue(vBar->value() + 10);
    }

    if (view->mouseTouchesLeftBorder(viewCoords)) {
        hBar->setValue(hBar->value() - 10);
    } else if (view->mouseTouchesRightBorder(viewCoords)) {
        hBar->setValue(hBar->value() + 10);
    }

    auto sceneCoords = view->mapToScene(mouseEvent->pos());
    view->emit needNewTempPreviewNode(sceneCoords.x(), sceneCoords.y());
}

void MapViewAddNodeState::mousePressEvent(MapView *view, QMouseEvent *mouseEvent)  {
    view->triggerParentMousePressEvent(mouseEvent);

    if (mouseEvent->buttons().testFlag(Qt::RightButton)) {
        view->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

void MapViewAddNodeState::mouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        auto coords = view->mapToScene(mouseEvent->pos());
        view->emit needNewRouteNode(coords.x(), coords.y());
    } else if (mouseEvent->button() == Qt::RightButton) {
        view->setDragMode(QGraphicsView::NoDrag);
    }
}

void MapViewAddNodeState::mouseLeaveEvent(MapView *view, QEvent *mouseEvent) {
    view->emit needTempPreviewNodeRemoved();
}
