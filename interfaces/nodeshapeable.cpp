#include "nodeshapeable.h"
#include <QFont>
#include <QDebug>

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
    if (brush.color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setPen(QPen(Qt::white));
    } else {
        setPen(QPen(Qt::black));
    }

    setBrush(brush);

    nodeLabel.setText(text);
    nodeLabel.setBrush(this->pen().brush());
    auto nodeLabelMidX = midX - nodeLabel.boundingRect().width()/2;
    auto nodeLabelMidY = midY - nodeLabel.boundingRect().height()/2;
    nodeLabel.setPos(nodeLabelMidX, nodeLabelMidY);

    extraTextLabel.setText("Info");
    extraTextLabel.setBrush(this->brush());
    auto extraTextPen = this->pen();
    extraTextPen.setWidthF(0.3);
    extraTextLabel.setPen(extraTextPen);
    extraTextLabel.setPos(nodeLabelMidX + 20, nodeLabelMidY);
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

