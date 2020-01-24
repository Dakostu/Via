#include "routenode.h"
#include <QGraphicsSceneMouseEvent>

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText, std::unique_ptr<UIState> &state)
    : node(newNode),
      nodeLabel(nodeLabelText),
      extraTextLabel(extraTextLabelText, node.get()),
      styleDiffersFromRoute(false),
      currentState(state)
{

    setDefaultColors();

    setFlag(ItemIsMovable);
    acceptHoverEvents();

    nodeLabel.setColors(node->pen().brush().color());
    extraTextLabel.setColors(node->pen().brush().color());

    centerNodeLabelBox();

    addToGroup(node.get());
    addToGroup(&nodeLabel);

    auto center = node->boundingRect().center();
    extraTextLabel.setPos(center.x() + (90 * elementSize - 60), center.y() - extraTextLabel.boundingRect().height() / 2);
}

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText, std::unique_ptr<UIState> &state) :
    RouteNode(newNode, nodeLabelText, "", state) {}

void RouteNode::setElementSize(int newSize) {
    elementSize = newSize;
    node->setElementSize(newSize);
    extraTextLabel.setElementSize(newSize);
    nodeLabel.setElementSize(newSize);
    centerNodeLabelBox();
    std::for_each(toConnections.begin(), toConnections.end(), [&](auto &conn) { conn->setElementSize(newSize); });
}

void RouteNode::setColors(const QColor &color) {
    node->setColors(color);
    nodeLabel.setColors(color);
    extraTextLabel.setColors(color);
    std::for_each(toConnections.begin(), toConnections.end(), [&](auto &conn) { conn->setColors(color); });
}

QColor RouteNode::getColor() const {
    return node->brush().color();
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
    currentState->routeNodeMouseHoverEnterEvent(this, hoverEvent);
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
    currentState->routeNodeMouseMoveEvent(this, mouseEvent);
}

void RouteNode::triggerParentMouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItemGroup::mouseMoveEvent(mouseEvent);
}

ConnectionVector* RouteNode::getFromConnections() {
    return &fromConnections;
}

ConnectionVector* RouteNode::getToConnections() {
    return &toConnections;
}
