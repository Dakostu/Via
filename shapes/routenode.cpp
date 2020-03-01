#include "routenode.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

using namespace Via::Shapes;
using namespace Via::Interfaces;
using namespace Via::Control;
using namespace Via::UI;

RouteNode::RouteNode(RouteNodeShape *newNode, QString nodeLabelText, QString extraTextLabelText, std::unique_ptr<RouteNodeState> &state)
    : node(newNode),
      nodeLabel(nodeLabelText),
      extraTextLabel(extraTextLabelText, node.get()),
      styleDiffersFromRoute(false),
      fromConnection(nullptr),
      toConnection(nullptr),
      currentState(state)
{

    activateColors();

    setFlag(ItemIsMovable);
    acceptHoverEvents();

    nodeLabel.setColors(node->pen().brush().color());
    nodeLabel.setZValue(std::numeric_limits<qreal>::max());
    extraTextLabel.setColors(node->pen().brush().color());

    centerNodeLabelBox();

    addToGroup(node.get());
    addToGroup(&nodeLabel);        

    auto center = node->boundingRect().center();
    extraTextLabel.setPos(center.x() + (90 * elementSize - 60), center.y() - extraTextLabel.boundingRect().height() / 2);

    this->setZValue(std::numeric_limits<qreal>::max());
}

RouteNode::RouteNode(RouteNodeShape *newNode, QString nodeLabelText, std::unique_ptr<RouteNodeState> &state) :
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

    activateColors();
}

QColor RouteNode::getColor() const {
    return node->brush().color();
}

void RouteNode::activateColors() {
    node->activateColors();
    nodeLabel.setColors(node->pen().brush().color());
    extraTextLabel.setColors(node->pen().brush().color());
    if (toConnection) {
        toConnection->activateColors();
    }
}

RouteNodeLabel* RouteNode::getNodeLabel()
{
    return &nodeLabel;
}

bool RouteNode::getStyleDiffersFromRoute() const
{
    return styleDiffersFromRoute;
}

void RouteNode::setStyleDiffersFromRoute(bool value)
{
    styleDiffersFromRoute = value;
}

RouteNodeShape* RouteNode::getNodeShape() const
{
    return node.get();
}

void RouteNode::centerNodeLabelBox() {
    auto center = node->boundingRect().center();
    auto nodeLabelBox = nodeLabel.boundingRect();
    nodeLabel.setPos(center.x() - nodeLabelBox.width()/2, center.y() - nodeLabelBox.height()/2);
}

void RouteNode::hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) {
    currentState->mouseHoverEnterEvent(this, hoverEvent);
    QGraphicsItemGroup::hoverEnterEvent(hoverEvent);
}

void RouteNode::hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) {
    currentState->mouseHoverLeaveEvent(this, hoverEvent);
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

void RouteNode::setShape(RouteNodeShape* newShape) {
    removeFromGroup(this->node.get());
    node.reset(newShape);
    addToGroup(newShape);
}

void RouteNode::resetFromConnection() {
    fromConnection = nullptr;
}

void RouteNode::resetToConnection() {
    toConnection.reset(nullptr);
}

void RouteNode::checkIfStyleIsDifferent(char routeShape, const QColor &routeColor, int routeSize) {
    setStyleDiffersFromRoute(routeShape != this->node->getShapeKey() || routeColor != this->getColor() || routeSize != this->elementSize);
}

RouteExtraTextLabel* RouteNode::getExtraText() {
    return &extraTextLabel;
}

void RouteNode::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    currentState->mouseMoveEvent(this, mouseEvent);
}

void RouteNode::triggerParentMouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItemGroup::mouseMoveEvent(mouseEvent);
}

void RouteNode::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    currentState->mousePressEvent(this, mouseEvent);
    QGraphicsItemGroup::mousePressEvent(mouseEvent);
}

void RouteNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    currentState->mouseReleaseEvent(this, mouseEvent);
    QGraphicsItemGroup::mouseReleaseEvent(mouseEvent);
}

RouteConnection* RouteNode::getFromConnection() {
    return fromConnection;
}

RouteConnection* RouteNode::getToConnection() {
    return toConnection.get();
}

void RouteNode::connect(RouteNode &from) {
    auto color = node->brush().color();
    auto connection = new RouteConnection(from.boundingRect().center() + from.pos(), this->boundingRect().center(), color);
    connection->setElementSize(elementSize);
    from.toConnection.reset(connection);
    fromConnection = connection;
}

void RouteNode::swap(RouteNode *with) {
    auto tempCenter = with->getCenter();
    auto tempColor = with->getColor();
    auto tempSize = with->getElementSize();
    auto tempExtraLabelText = with->getExtraText()->text();
    auto tempStyleIsDifferent = with->getStyleDiffersFromRoute();


    with->getExtraText()->setText(this->getExtraText()->text());
    with->setStyleDiffersFromRoute(this->styleDiffersFromRoute);
    with->moveBy(this->getCenter().x() - with->getCenter().x(), this->getCenter().y() - with->getCenter().y());
    if (this->styleDiffersFromRoute) {
        with->setColors(this->getColor());
        with->setElementSize(this->elementSize);
        //shape
    }

    this->getExtraText()->setText(tempExtraLabelText);
    this->setStyleDiffersFromRoute(tempStyleIsDifferent);
    this->moveBy(tempCenter.x() - this->getCenter().x(), tempCenter.y() - this->getCenter().y());
    if (tempStyleIsDifferent) {
        this->setColors(tempColor);
        this->setElementSize(tempSize);
        // shape
    }
}

QPointF RouteNode::getCenter() {
    return this->boundingRect().center() + this->pos();
}

void RouteNode::updateRouteConnections() {
    auto thisPos = this->getCenter();

    if (auto fromConn = this->getFromConnection()) {
        auto fromNodePos = fromConn->p1();
        fromConn->setNewPosition(fromNodePos, thisPos);
    }

    if (auto toConn = this->getToConnection()) {
        auto toNodePos = toConn->p2();
        toConn->setNewPosition(thisPos, toNodePos);
    }
}

void RouteNode::moveBy(qreal dx, qreal dy) {
    QGraphicsItem::moveBy(dx, dy);
    this->updateRouteConnections();
}
