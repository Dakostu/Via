#include "../model/routedata.h"
#include "../model/routenodedata.h"
#include "routenode.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QJsonArray>

using namespace Via::Shapes;
using namespace Via::Interfaces;
using namespace Via::Control;
using namespace Via::UI;
using namespace Via::Model;

RouteNode::RouteNode(RouteNodeShape *newNode, const QString &nodeLabelText,
                     const QString &extraTextLabelText, std::unique_ptr<RouteNodeState> &state)
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

RouteNode::RouteNode(RouteNodeShape *newNode, const QString &nodeLabelText, std::unique_ptr<RouteNodeState> &state) :
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

    activateColors();
}

void RouteNode::setToConnectionColor(const QColor &color) {
    if (toConnection) {
        toConnection->setColors(color);
    }
}

QColor RouteNode::getColors() const {
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


void RouteNode::fromJSON(const QJsonObject &object) {
    name = object[RouteNodeData::NODE_NAME_KEY].toString();
    nodeLabel.setText(object[RouteNodeData::NODE_LABEL_KEY].toString());

    //setPos(object[RouteNodeData::NODE_X_KEY].toInt(), object[RouteNodeData::NODE_Y_KEY].toInt());
    styleDiffersFromRoute = object[RouteNodeData::NODE_DIFFERENT_STYLE_KEY].toBool();
    nameChangedByUser = object[RouteNodeData::NODE_NAME_CHANGED_KEY].toBool();
    //invisible = object[RouteNodeData::NODE_INVISIBLE_KEY].toBool();

    if (styleDiffersFromRoute) {
        setColors(QColor(object[RouteNodeData::NODE_COLOR_KEY][0].toInt(), object[RouteNodeData::NODE_COLOR_KEY][1].toInt(), object[RouteNodeData::NODE_COLOR_KEY][2].toInt()));
        elementSize = object[RouteNodeData::NODE_SIZE_KEY].toInt();
    }
}

QJsonObject RouteNode::toJSON() {
    QJsonObject routeNodeJSON;

    const auto pos = getCenter();

    routeNodeJSON[RouteNodeData::NODE_NAME_KEY] = name;
    routeNodeJSON[RouteNodeData::NODE_LABEL_KEY] = nodeLabel.text();
    routeNodeJSON[RouteNodeData::NODE_X_KEY] = std::round(pos.x());
    routeNodeJSON[RouteNodeData::NODE_Y_KEY] = std::round(pos.y());
    routeNodeJSON[RouteNodeData::NODE_DIFFERENT_STYLE_KEY] = styleDiffersFromRoute;
    routeNodeJSON[RouteNodeData::NODE_NAME_CHANGED_KEY] = nameChangedByUser;
    //routeNodeJSON[RouteNodeData::NODE_INVISIBLE_KEY] = false;

    if (styleDiffersFromRoute) {
        auto currentColor = getColors();
        routeNodeJSON[RouteNodeData::NODE_COLOR_KEY] = QJsonArray({currentColor.red(), currentColor.green(), currentColor.blue()});
        routeNodeJSON[RouteNodeData::NODE_SIZE_KEY] = elementSize;
        routeNodeJSON[RouteNodeData::NODE_SHAPE_KEY] = getShapeKey();
    }

    return routeNodeJSON;

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

char RouteNode::getShapeKey() const {
    return node->getShapeKey();
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
    centerNodeLabelBox();
}

void RouteNode::setShape(RouteNodeShape* newShape) {
    removeFromGroup(this->node.get());
    node.reset(newShape);
    addToGroup(newShape);
    centerNodeLabelBox();
}

void RouteNode::resetFromConnection() {
    fromConnection = nullptr;
}

void RouteNode::resetToConnection() {
    toConnection.reset(nullptr);
}

void RouteNode::resetConnections() {
    resetFromConnection();
    resetToConnection();
}

void RouteNode::checkIfStyleIsDifferent(char routeShape, const QColor &routeColor, int routeSize) {
    setStyleDiffersFromRoute(routeShape != this->node->getShapeKey() || routeColor != this->getColors() || routeSize != this->elementSize);
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


QPointF RouteNode::getCenter() const {
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
