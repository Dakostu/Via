#include "mapviewaddnodestate.h"
#include "../../ui/mapview.h"

#include <QDebug>

using namespace Via::Control;
using namespace Via::UI;

void MapViewAddNodeState::mouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    if (!mouseEvent->buttons().testFlag(Qt::RightButton)) {
        view->setDragMode(QGraphicsView::NoDrag);
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        view->setCursor(Qt::CrossCursor);
    }

    auto viewCoords = mouseEvent->pos();

    if (view->mouseTouchesTopBorder(viewCoords)) {
        qDebug() << "Top";
    } else if (view->mouseTouchesBottomBorder(viewCoords)) {
        qDebug() << "Bottom";
    }

    if (view->mouseTouchesLeftBorder(viewCoords)) {
        qDebug() << "Left";
    } else if (view->mouseTouchesRightBorder(viewCoords)) {
        qDebug() << "Right";
    }


    qDebug() << mouseEvent->pos();

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
