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

public:

    virtual ~UIState();

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) = 0;   

    virtual void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) = 0;
    virtual void routeNodeMouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) = 0;
    virtual void routeNodeMousePressEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) = 0;
    virtual void routeNodeMouseReleaseEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) = 0;

    virtual void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) = 0;

};

#endif // UISTATE_H
