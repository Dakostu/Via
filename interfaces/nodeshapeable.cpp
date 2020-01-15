#include "nodeshapeable.h"
#include <QFont>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>


void NodeShapeable::setSize(qreal newSize) {
    ViewCustomizable::setSize(newSize);
    this->drawShape();
}

NodeShapeable::NodeShapeable(qreal x, qreal y, QBrush brush)
    : QGraphicsPolygonItem({}, nullptr), originX(x), originY(y)
{
    this->setBrush(brush);

    this->setFlag(ItemIsFocusable);
    this->setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);
}


void NodeShapeable::setColors(const QColor &color) {
    setPen(QPen(color));
}

void NodeShapeable::setDefaultColors() {
    if (this->brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setColors(Qt::white);
    } else {
        setColors(Qt::black);
    }
}
