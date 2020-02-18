#include "../../ui/mapview.h"
#include "mapviewmovenodestate.h"
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>
#include <QScrollBar>

using namespace Via::Control;
using namespace Via::UI;

MapViewMoveNodeState::MapViewMoveNodeState()
{

}

void MapViewMoveNodeState::mouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->triggerParentMouseMoveEvent(mouseEvent);
    if (mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        const QRect screenRect = QApplication::desktop()->screenGeometry(view);
        auto eventPos = mouseEvent->globalPos();
        auto hBar = view->horizontalScrollBar();
        auto vBar = view->verticalScrollBar();

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
            view->setDragMode(QGraphicsView::NoDrag);
            QCursor::setPos(eventPos);
            view->setDragMode(QGraphicsView::ScrollHandDrag);
        } else if (mouseEvent->globalY() != eventPos.y()) {
            view->setDragMode(QGraphicsView::NoDrag);
            QCursor::setPos(eventPos);
            view->setDragMode(QGraphicsView::ScrollHandDrag);
        }
    }
}

void MapViewMoveNodeState::mousePressEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMousePressEvent(mouseEvent);
}

void MapViewMoveNodeState::mouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMouseReleaseEvent(mouseEvent);
}
