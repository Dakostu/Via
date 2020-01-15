#include "nodeshapeable.h"
#include <QFont>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

qreal NodeShapeable::sizeMultiplier(qreal val) {
    return val * size;
}

qreal NodeShapeable::getSize() {
    return size;
}

void NodeShapeable::setSize(qreal newSize) {
    size = newSize;
    auto font = nodeLabel.font();
    font.setPointSizeF(newSize / 2 + 7);
    nodeLabel.setFont(font);
    nodeLabel.setPos(midX - nodeLabel.boundingRect().width()/2, midY - nodeLabel.boundingRect().height()/2);

    this->drawShape();
}

NodeShapeable::NodeShapeable(qreal x, qreal y, QBrush brush, QString text)
    : QGraphicsPolygonItem({}, nullptr), midX(x), midY(y)
{

    setBrush(brush);

    nodeLabel.setText(text);
    auto nodeLabelMidX = midX - nodeLabel.boundingRect().width()/2;
    auto nodeLabelMidY = midY - nodeLabel.boundingRect().height()/2;
    nodeLabel.setPos(nodeLabelMidX, nodeLabelMidY);

    extraTextLabel.setText("Info");
    extraTextLabel.setBrush(this->brush());
    extraTextLabel.setPos(nodeLabelMidX + 20, nodeLabelMidY);

    this->setFlag(ItemIsFocusable);
    this->setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);

    setDefaultPenColor();
}

QPointF NodeShapeable::getCenter() {
    return {midX, midY};
}

QGraphicsSimpleTextItem* NodeShapeable::getNodeLabel() {
     return &nodeLabel;
}

QGraphicsSimpleTextItem* NodeShapeable::getExtraTextLabel() {
     return &extraTextLabel;
}

void NodeShapeable::hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) {

    auto rgb = this->brush().color().rgb();
    auto invertedRgb = QColor(~rgb);
    setPenColor(invertedRgb);
    QGraphicsPolygonItem::hoverEnterEvent(hoverEvent);
}

void NodeShapeable::hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) {
    setDefaultPenColor();
    QGraphicsPolygonItem::hoverLeaveEvent(hoverEvent);
}

void NodeShapeable::setDefaultPenColor() {
    if (brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setPenColor(Qt::white);
    } else {
        setPenColor(Qt::black);
    }
}

void NodeShapeable::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    QGraphicsPolygonItem::mouseMoveEvent(mouseEvent);
    qDebug() << mouseEvent;
    //midX = mapToScene(mouseEvent->scenePos()).x();
    //midX = mapToScene(mouseEvent->scenePos()).y();

    //auto nodeLabelMidX = midX - nodeLabel.boundingRect().width()/2;
    //auto nodeLabelMidY = midY - nodeLabel.boundingRect().height()/2;
//    nodeLabel.setPos(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    midX += this->pos().x();
    midY += this->pos().y();
    qDebug() << midX << midY;
    qDebug() << this->pos();

    //nodeLabel.setPos(midX + this->pos().x(), midY + this->pos().y());
    //auto nodeLabelMidX = midX - nodeLabel.boundingRect().width()/2;
    //auto nodeLabelMidY = midY - nodeLabel.boundingRect().height()/2;
    //nodeLabel.setPos(nodeLabelMidX, nodeLabelMidY);
    //extraTextLabel.setPos(nodeLabelMidX + 20, nodeLabelMidY);
}

void NodeShapeable::setPenColor(const QColor &color) {
    setPen(QPen(color));
    nodeLabel.setBrush(this->pen().brush());
    auto extraTextPen = this->pen();
    extraTextPen.setWidthF(size);
    extraTextLabel.setPen(extraTextPen);
}
