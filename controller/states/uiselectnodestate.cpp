#include "uiselectnodestate.h"

using namespace Via::Control;
using namespace Via::UI;

void UISelectNodeState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(false);
    quickButtonMove->setChecked(false);
    quickButtonSelect->setChecked(true);
}

void UISelectNodeState::mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->setDragMode(QGraphicsView::NoDrag);
}

void UISelectNodeState::mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMousePressEvent(mouseEvent);
}

void UISelectNodeState::mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {
    view->triggerParentMouseReleaseEvent(mouseEvent);
}
