#include "routenode.h"
#include <QGraphicsSceneMouseEvent>

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText)
    : node(newNode), nodeLabel(nodeLabelText), extraTextLabel(extraTextLabelText, node.get()),
    styleDiffersFromRoute(false)
{

    setDefaultColors();

    acceptHoverEvents();
    setFlag(ItemIsMovable);

    nodeLabel.setColors(node->pen().brush().color());
    extraTextLabel.setColors(node->pen().brush().color());

    centerNodeLabelBox();

    addToGroup(node.get());
    addToGroup(&nodeLabel);

    auto center = node->boundingRect().center();
    extraTextLabel.setPos(center.x() + (90 * elementSize - 60), center.y() - extraTextLabel.boundingRect().height() / 2);
}

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText) :
    RouteNode(newNode, nodeLabelText, "") {}

void RouteNode::setElementSize(qreal newSize) {
    elementSize = newSize;
    node->setElementSize(newSize);
    extraTextLabel.setElementSize(newSize);
    nodeLabel.setElementSize(newSize);
    centerNodeLabelBox();
    std::for_each(toConnections.begin(), toConnections.end(), [&](auto &conn) { conn->setElementSize(newSize); });
}

void RouteNode::setColors(const QColor &color) {
    node->setColors(color);
    extraTextLabel.setColors(color);
    nodeLabel.setColors(color);
    std::for_each(toConnections.begin(), toConnections.end(), [&](auto &conn) { conn->setColors(color); });
}

void RouteNode::setDefaultColors() {
    node->setDefaultColors();
    nodeLabel.setColors(node->pen().brush().color());
    extraTextLabel.setColors(node->pen().brush().color());
    std::for_each(toConnections.begin(), toConnections.end(), [&](auto &conn) { conn->setDefaultColors(); });
}

void RouteNode::centerNodeLabelBox() {
    auto center = node->boundingRect().center();
    auto nodeLabelBox = nodeLabel.boundingRect();
    nodeLabel.setPos(center.x() - nodeLabelBox.width()/2, center.y() - nodeLabelBox.height()/2);
}

void RouteNode::hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) {
    auto nodeColorInverted = ~(node->brush().color().rgb());
    node->setColors(nodeColorInverted);
    nodeLabel.setColors(nodeColorInverted);
    extraTextLabel.setColors(nodeColorInverted);
    QGraphicsItemGroup::hoverEnterEvent(hoverEvent);
}

void RouteNode::hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) {
    setDefaultColors();
    QGraphicsItemGroup::hoverLeaveEvent(hoverEvent);
}

void RouteNode::setOpacity(qreal opacity) {
    QGraphicsItem::setOpacity(opacity);
    nodeLabel.setOpacity(opacity);
    extraTextLabel.setOpacity(opacity);
}

void RouteNode::setNodeLabelOpacity(qreal opacity) {
    nodeLabel.setOpacity(opacity);
}

bool RouteNode::isInvisible() {
    return opacity() < 0.000001;
}

RouteExtraTextLabel* RouteNode::getExtraText() {
    return &extraTextLabel;
}

void RouteNode::connect(RouteNode &from) {
    auto color = node->brush().color();
    auto connection = new RouteConnection(from.boundingRect().center(), this->boundingRect().center(), color);
    connection->setElementSize(elementSize);
    this->fromConnections.emplace_back(connection);
    from.toConnections.emplace_back(connection);
}

void RouteNode::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        auto thisPos = this->boundingRect().center() + this->pos();
        for (auto &conn : fromConnections) {
            auto fromNodePos = conn->p1();
            conn->setNewPosition(fromNodePos, thisPos);
        }
        for (auto &conn : toConnections) {
            auto toNodePos = conn->p2();
            conn->setNewPosition(thisPos, toNodePos);
        }
    }
    QGraphicsItemGroup::mouseMoveEvent(mouseEvent);
}

ConnectionVector* RouteNode::getToConnections() {
    return &toConnections;
}
