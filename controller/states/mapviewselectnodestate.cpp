#include "mapviewselectnodestate.h"

using namespace Via::Control;
using namespace Via::UI;

MapViewSelectNodeState::MapViewSelectNodeState()
{

}

void mouseMoveEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent) {
    view.setDragMode(QGraphicsView::NoDrag);
}

void mousePressEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent) {
    view.triggerParentMousePressEvent(mouseEvent);
}

void mouseReleaseEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent) {
    view.triggerParentMouseReleaseEvent(mouseEvent);
}
