#include "nodeshapeable.h"

int NodeShapeable::sizeMultiplier(int val) {
    return val * size;
}

int NodeShapeable::getSize() {
    return size;
}

void NodeShapeable::setSize(int newSize) {
    size = newSize;
}

NodeShapeable::NodeShapeable(const QVector<QPointF> &points, QBrush brush, QPen pen, QGraphicsItem *scene, QString text)
    : QGraphicsPolygonItem(points, scene), nodeText(text)
{
    this->setPen(pen);
    this->setBrush(brush);
}
