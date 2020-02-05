#ifndef UISTATE_H
#define UISTATE_H

#include "../shapes/routenode.h"
#include "../ui/mapview.h"

#include <QAbstractButton>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

namespace Via::Shapes {
    class RouteNode;
    class Route;
}

namespace Via::UI {
    class MapView;
}

namespace Via::Control {

class UIState
{
protected:
    UIState() {}

public:   
    virtual ~UIState() {}

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) {}

    virtual void routeNodeMouseHoverEnterEvent(Via::Shapes::RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {}
    virtual void routeNodeMouseHoverLeaveEvent(Via::Shapes::RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {}
    virtual void routeNodeMouseMoveEvent(Via::Shapes::RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {}
    virtual void routeNodeMousePressEvent(Via::Shapes::RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {}
    virtual void routeNodeMouseReleaseEvent(Via::Shapes::RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {}

    virtual void mapViewMouseMoveEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) {}
    virtual void mapViewMousePressEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) {}
    virtual void mapViewMouseReleaseEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) {}
    virtual void mapViewMouseLeaveEvent(Via::UI::MapView *view, QEvent *mouseEvent) {}

};

}

#endif // UISTATE_H
