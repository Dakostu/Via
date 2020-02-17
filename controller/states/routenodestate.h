#ifndef ROUTENODESTATE_H
#define ROUTENODESTATE_H

#include "../../shapes/routenode.h"

#include <QGraphicsSceneHoverEvent>

namespace Via::Control {

class RouteNodeState : public UIState
{
protected:    
    RouteNodeState();

public:
    virtual ~RouteNodeState();

    virtual void mouseHoverEnterEvent(Via::Shapes::RouteNode& node, QGraphicsSceneHoverEvent *hoverEvent);
    virtual void mouseHoverLeaveEvent(Via::Shapes::RouteNode& node, QGraphicsSceneHoverEvent *hoverEvent);
    virtual void mouseMoveEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent);

};

}

#endif // ROUTENODESTATE_H
