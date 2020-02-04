#ifndef UISTATE_H
#define UISTATE_H

#include "../shapes/routenode.h"
#include "../ui/mapview.h"

#include <QAbstractButton>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

class RouteNode;
class Route;
class MapView;

class UIState
{
protected:
    UIState() {}

public:   
    virtual ~UIState() {}

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) {}

    virtual void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {}
    virtual void routeNodeMouseHoverLeaveEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {}
    virtual void routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {}
    virtual void routeNodeMousePressEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {}
    virtual void routeNodeMouseReleaseEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {}

    virtual void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) {}
    virtual void mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) {}
    virtual void mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) {}

};

#endif // UISTATE_H
