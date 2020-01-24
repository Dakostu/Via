#include "uiselectnodestate.h"


void UISelectNodeState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(false);
    quickButtonMove->setChecked(false);
    quickButtonSelect->setChecked(true);
}

void UISelectNodeState::routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {

}

void UISelectNodeState::routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {
}
