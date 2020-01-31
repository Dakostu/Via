#ifndef UIADDNODESTATE_H
#define UIADDNODESTATE_H

#include "uistate.h"

class UIAddNodeState : public UIState
{
public:

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;

    virtual void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;
    virtual void routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void routeNodeMousePressEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void routeNodeMouseReleaseEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) override;

    virtual void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) override;
    virtual void mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) override;
    virtual void mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) override;
};

#endif // UIADDNODESTATE_H
