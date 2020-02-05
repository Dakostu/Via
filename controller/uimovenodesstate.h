#ifndef UIMOVENODESSTATE_H
#define UIMOVENODESSTATE_H

#include "uistate.h"

class UIMoveNodesState : public UIState
{
public:
    void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                          QAbstractButton *quickButtonMove,
                          QAbstractButton *quickButtonSelect) override;

    void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;
    void routeNodeMouseHoverLeaveEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;
    void routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;
    void routeNodeMousePressEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;
    void routeNodeMouseReleaseEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;

    void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) override;
};

#endif // UIMOVENODESSTATE_H
