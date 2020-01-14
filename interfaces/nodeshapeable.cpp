#include "nodeshapeable.h"

qreal NodeShapeable::sizeMultiplier(qreal val) {
    return val * size;
}

qreal NodeShapeable::getSize() {
    return size;
}

void NodeShapeable::setSize(qreal newSize) {
    size = newSize;
}

NodeShapeable::NodeShapeable(qreal x, qreal y, QBrush brush, QPen pen, QString text)
    : QGraphicsPolygonItem({}, nullptr), midX(x), midY(y)
{
    this->setPen(pen);
    this->setBrush(brush);
    this->nodeText.setText(text);
    this->nodeText.setBrush(pen.brush());
    this->nodeText.setPos(x,y);
}

QPointF NodeShapeable::getCenter() {
    return {midX, midY};
}


QGraphicsSimpleTextItem* NodeShapeable::getText() {
     return &nodeText;
}
