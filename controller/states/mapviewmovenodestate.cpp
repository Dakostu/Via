#include "../../ui/mapview.h"
#include "mapviewmovenodestate.h"
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>
#include <QEvent>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
using namespace Via::Control;
using namespace Via::UI;


void MapViewMoveNodeState::mouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->triggerParentMouseMoveEvent(mouseEvent);
    if (mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        auto eventPos = mouseEvent->pos();
        auto globalPos = view->mapToGlobal(eventPos);
        auto viewPort = view->viewport();

        auto moveCursorTo = [&](int x, int y) {
            auto r_event = QMouseEvent(QEvent::MouseButtonRelease, globalPos, Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
            view->triggerParentMouseReleaseEvent(&r_event);
            QCursor::setPos(x, y);
            QTimer::singleShot(100, [&]() {
                //this->mousePressEvent(view, new QMouseEvent(QEvent::MouseButtonPress, view->mapToScene(x,y), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier));
            } );

        };

        qDebug() << eventPos << globalPos << mouseEvent->localPos();


        if (view->mouseTouchesTopBorder(eventPos)) {
            auto bottomBorderPos = viewPort->mapToGlobal(viewPort->pos()).y() + viewPort->height();

            moveCursorTo(globalPos.x(), bottomBorderPos - view->BORDER_PUFFER_POS - BORDER_MOVE_PUFFER);
        } else if (view->mouseTouchesBottomBorder(eventPos)) {
            auto topBorderPos = viewPort->mapToGlobal(viewPort->pos()).y();

            moveCursorTo(globalPos.x(), topBorderPos + view->BORDER_PUFFER_POS + BORDER_MOVE_PUFFER);
        }

        if (view->mouseTouchesLeftBorder(eventPos)) {
            auto rightBorderPos = viewPort->mapToGlobal(viewPort->pos()).x() + viewPort->width();

            moveCursorTo(rightBorderPos - view->BORDER_PUFFER_POS - BORDER_MOVE_PUFFER, globalPos.y());
        } else if (view->mouseTouchesRightBorder(eventPos)) {
            auto leftBorderPos = viewPort->mapToGlobal(viewPort->pos()).x();

            moveCursorTo(leftBorderPos + view->BORDER_PUFFER_POS + BORDER_MOVE_PUFFER, globalPos.y());
        }

    }
}

void MapViewMoveNodeState::mousePressEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMousePressEvent(mouseEvent);
}

void MapViewMoveNodeState::mouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMouseReleaseEvent(mouseEvent);
}
