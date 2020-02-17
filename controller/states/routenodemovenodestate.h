#ifndef ROUTENODEMOVENODESTATE_H
#define ROUTENODEMOVENODESTATE_H

#include "routenodestate.h"

namespace Via::Control {

class RouteNodeMoveNodeState : public RouteNodeState
{
public:
    RouteNodeMoveNodeState();

    void mouseHoverEnterEvent(Via::Shapes::RouteNode& node, QGraphicsSceneHoverEvent *hoverEvent) override;
    void mouseHoverLeaveEvent(Via::Shapes::RouteNode& node, QGraphicsSceneHoverEvent *hoverEvent) override;
    void mouseMoveEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent) override;
};

}

#endif // ROUTENODEMOVENODESTATE_H
