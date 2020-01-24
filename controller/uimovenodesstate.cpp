#include "uimovenodesstate.h"


void UIMoveNodesState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(false);
    quickButtonMove->setChecked(true);
    quickButtonSelect->setChecked(false);
}

void UIMoveNodesState::routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {
    auto nodeColorInverted = ~(node->getColor().rgb());
    node->setColors(nodeColorInverted);
}
