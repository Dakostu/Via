#include "../../ui/mapview.h"
#include "mapviewselectnodestate.h"

using namespace Via::Control;
using namespace Via::UI;

MapViewSelectNodeState::MapViewSelectNodeState()
{

}

void mouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->setDragMode(QGraphicsView::NoDrag);
}

void mousePressEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMousePressEvent(mouseEvent);
}

void mouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMouseReleaseEvent(mouseEvent);
}
