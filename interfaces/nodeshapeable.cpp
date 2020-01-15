#include "nodeshapeable.h"
#include <QFont>

qreal NodeShapeable::sizeMultiplier(qreal val) {
    return val * size;
}

qreal NodeShapeable::getSize() {
    return size;
}

void NodeShapeable::setSize(qreal newSize) {
    size = newSize;
    auto font = nodeText.font();
    font.setPointSizeF(newSize / 2 + 7);
    nodeText.setFont(font);
    nodeText.setPos(midX - nodeText.boundingRect().width()/2, midY - nodeText.boundingRect().height()/2);

    this->drawShape();
}

NodeShapeable::NodeShapeable(qreal x, qreal y, QBrush brush, QPen pen, QString text)
    : QGraphicsPolygonItem({}, nullptr), midX(x), midY(y)
{
    setPen(pen);
    setBrush(brush);
    nodeText.setText(text);
    nodeText.setBrush(pen.brush());
    nodeText.setPos(x - nodeText.boundingRect().width()/2,y - nodeText.boundingRect().height()/2);
}

QPointF NodeShapeable::getCenter() {
    return {midX, midY};
}


QGraphicsSimpleTextItem* NodeShapeable::getText() {
     return &nodeText;
}
