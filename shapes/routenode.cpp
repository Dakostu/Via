#include "routenode.h"

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText)
    : node(newNode), nodeLabel(nodeLabelText), extraTextLabel(extraTextLabelText) {

    setDefaultColors();

    setAcceptHoverEvents(true);
    this->setFlag(ItemIsMovable);


    this->addToGroup(node.get());

    nodeLabel.setBrush(node->pen().brush());
    centerNodeLabelBox();
    this->addToGroup(&nodeLabel);

    auto center = node->boundingRect().center();
    extraTextLabel.setPos(center.x() + 10 * size, center.y());
}

RouteNode::RouteNode(NodeShapeable *newNode, QString nodeLabelText) :
    RouteNode(newNode, nodeLabelText, "") {}

void RouteNode::setSize(qreal newSize) {
    node->setSize(newSize);
    extraTextLabel.setSize(newSize);
    nodeLabel.setSize(newSize);
    centerNodeLabelBox();
}

void RouteNode::setColors(const QColor &color) {
    node->setColors(color);
    extraTextLabel.setColors(color);
    nodeLabel.setColors(color);
}

void RouteNode::setDefaultColors() {
    node->setDefaultColors();
    extraTextLabel.setDefaultColors();
    nodeLabel.setColors(node->pen().brush().color());
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

RouteExtraTextLabel* RouteNode::getExtraText() {
    return &extraTextLabel;
}
