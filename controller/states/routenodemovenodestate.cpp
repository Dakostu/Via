#include "routenodemovenodestate.h"

#include <QCursor>

using namespace Via::Control;
using namespace Via::Shapes;

RouteNodeMoveNodeState::RouteNodeMoveNodeState()
{

}


void RouteNodeMoveNodeState::mouseHoverEnterEvent(Via::Shapes::RouteNode& node, QGraphicsSceneHoverEvent *hoverEvent) {
    auto nodeColorInverted = ~(node.getColor().rgb());
    node.setNodeOutlineColor(nodeColorInverted);
}

void RouteNodeMoveNodeState::mouseHoverLeaveEvent(Via::Shapes::RouteNode& node, QGraphicsSceneHoverEvent *hoverEvent) {
    node.activateColors();
}

void RouteNodeMoveNodeState::mouseMoveEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        node.updateRouteConnections();
    }

    node.triggerParentMouseMoveEvent(mouseEvent);
}

void RouteNodeMoveNodeState::mousePressEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent) {
    node.setCursor(Qt::ClosedHandCursor);
}

void RouteNodeMoveNodeState::mouseReleaseEvent(Via::Shapes::RouteNode& node, QGraphicsSceneMouseEvent *mouseEvent) {
    node.setCursor(Qt::OpenHandCursor);
}
