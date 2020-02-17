#include "../../shapes/routenode.h"
#include "routenodemovenodestate.h"
#include <QCursor>

using namespace Via::Control;
using namespace Via::Shapes;

RouteNodeMoveNodeState::RouteNodeMoveNodeState()
{

}


void RouteNodeMoveNodeState::mouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {
    auto nodeColorInverted = ~(node->getColor().rgb());
    node->setNodeOutlineColor(nodeColorInverted);
}

void RouteNodeMoveNodeState::mouseHoverLeaveEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) {
    node->activateColors();
}

void RouteNodeMoveNodeState::mouseMoveEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        node->updateRouteConnections();
    }

    node->triggerParentMouseMoveEvent(mouseEvent);
}

void RouteNodeMoveNodeState::mousePressEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {
    node->setCursor(Qt::ClosedHandCursor);
}

void RouteNodeMoveNodeState::mouseReleaseEvent(RouteNode *node, QGraphicsSceneMouseEvent *mouseEvent) {
    node->setCursor(Qt::OpenHandCursor);
}