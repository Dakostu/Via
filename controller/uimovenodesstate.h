#ifndef UIMOVENODESSTATE_H
#define UIMOVENODESSTATE_H

#include "uistate.h"

namespace Via::Control {

class UIMoveNodesState : public UIState
{
public:
    void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                          QAbstractButton *quickButtonMove,
                          QAbstractButton *quickButtonSelect) override;

    void routeNodeMouseHoverEnterEvent(Via::Shapes::RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;
    void routeNodeMouseHoverLeaveEvent(Via::Shapes::RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;
    void routeNodeMouseMoveEvent(Via::Shapes::RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;
    void routeNodeMousePressEvent(Via::Shapes::RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;
    void routeNodeMouseReleaseEvent(Via::Shapes::RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;

    void mapViewMouseMoveEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMousePressEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseReleaseEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
};

}

#endif // UIMOVENODESSTATE_H
