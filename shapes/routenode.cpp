#include "routenode.h"
#include <QGraphicsSceneMouseEvent>

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText, std::unique_ptr<UIState> &state)
    : node(newNode),
      nodeLabel(nodeLabelText),
      extraTextLabel(extraTextLabelText, node.get()),
      styleDiffersFromRoute(false),
      fromConnection(nullptr),
      toConnection(nullptr),
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

    this->setZValue(std::numeric_limits<qreal>::max());
}

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText, std::unique_ptr<UIState> &state) :
    RouteNode(newNode, nodeLabelText, "", state) {}

void RouteNode::setElementSize(int newSize) {
    elementSize = newSize;
    node->setElementSize(newSize);
    extraTextLabel.setElementSize(newSize);
    nodeLabel.setElementSize(newSize);
    centerNodeLabelBox();
    if (toConnection) {
        toConnection->setElementSize(newSize);
    }
}

void RouteNode::setColors(const QColor &color) {
    node->setColors(color);
    extraTextLabel.setColors(color);
    if (toConnection) {
        toConnection->setColors(color);
    }

    node->setDefaultColors();
    nodeLabel.setColors(node->pen().brush().color());
}

QColor RouteNode::getColor() const {
    return node->brush().color();
}

void RouteNode::setDefaultColors() {
    node->setDefaultColors();
    nodeLabel.setColors(node->pen().brush().color());
    extraTextLabel.setColors(node->pen().brush().color());
    if (toConnection) {
        toConnection->setDefaultColors();
    }
}

RouteNodeLabel* RouteNode::getNodeLabel()
{
    return &nodeLabel;
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
    currentState->routeNodeMouseHoverLeaveEvent(this, hoverEvent);
    QGraphicsItemGroup::hoverLeaveEvent(hoverEvent);
}

void RouteNode::setNodeOutlineColor(const QColor &color) {
    nodeLabel.setColors(color);
    node->setPen(color);
}

void RouteNode::setOpacity(qreal opacity) {
    QGraphicsItem::setOpacity(opacity);
    nodeLabel.setOpacity(opacity);
    extraTextLabel.setOpacity(opacity);
}

void RouteNode::setNodeLabelOpacity(qreal opacity) {
    nodeLabel.setOpacity(opacity);
}

void RouteNode::setNodeLabelText(const QString &newText) {
    nodeLabel.setText(newText);
}

void RouteNode::resetFromConnection() {
    fromConnection = nullptr;
}

void RouteNode::resetToConnection() {
    toConnection.reset(nullptr);
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
    from.toConnection.reset(connection);
    fromConnection = connection;
}

void RouteNode::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    currentState->routeNodeMouseMoveEvent(this, mouseEvent);
}

void RouteNode::triggerParentMouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItemGroup::mouseMoveEvent(mouseEvent);
}

void RouteNode::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    currentState->routeNodeMousePressEvent(this, mouseEvent);
    QGraphicsItemGroup::mousePressEvent(mouseEvent);
}

void RouteNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    currentState->routeNodeMouseReleaseEvent(this, mouseEvent);
    QGraphicsItemGroup::mouseReleaseEvent(mouseEvent);
}

RouteConnection* RouteNode::getFromConnection() {
    return fromConnection;
}

RouteConnection* RouteNode::getToConnection() {
    return toConnection.get();
}
