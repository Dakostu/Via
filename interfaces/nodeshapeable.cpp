#include "nodeshapeable.h"

qreal NodeShapeable::sizeMultiplier(qreal val) {
    return val * size;
}

qreal NodeShapeable::getSize() {
    return size;
}

void NodeShapeable::setSize(qreal newSize) {
    size = newSize;
    this->drawShape();
}

NodeShapeable::NodeShapeable(qreal x, qreal y, QBrush brush, QPen pen, QString text)
    : QGraphicsPolygonItem({}, nullptr), midX(x), midY(y)
{
    this->setPen(pen);
    this->setBrush(brush);
    this->nodeText.setText(text);
    this->nodeText.setBrush(pen.brush());
    this->nodeText.setPos(x - nodeText.boundingRect().width()/2,y - nodeText.boundingRect().height()/2);
}

QPointF NodeShapeable::getCenter() {
    return {midX, midY};
}


QGraphicsSimpleTextItem* NodeShapeable::getText() {
     return &nodeText;
}
