#include "uiaddnodestate.h"


void UIAddNodeState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(true);
    quickButtonMove->setChecked(false);
    quickButtonSelect->setChecked(false);
}


void UIAddNodeState::routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {

}

void UIAddNodeState::routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {

}
