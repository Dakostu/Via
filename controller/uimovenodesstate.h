#ifndef UIMOVENODESSTATE_H
#define UIMOVENODESSTATE_H

#include "uistate.h"

class UIMoveNodesState : public UIState
{
public:
    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;

    virtual void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;
    virtual void routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;
};

#endif // UIMOVENODESSTATE_H
