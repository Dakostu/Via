#include "../../ui/mapview.h"
#include "mapviewselectnodestate.h"

using namespace Via::Control;
using namespace Via::UI;


void MapViewSelectNodeState::mouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->setDragMode(QGraphicsView::NoDrag);
}

void MapViewSelectNodeState::mousePressEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMousePressEvent(mouseEvent);
}

void MapViewSelectNodeState::mouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMouseReleaseEvent(mouseEvent);
}
