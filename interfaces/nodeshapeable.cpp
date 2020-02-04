#include "nodeshapeable.h"
#include <QFont>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>


void NodeShapeable::setElementSize(int newSize) {
    ViewCustomizable::setElementSize(newSize);
    this->drawShape();
}

NodeShapeable::NodeShapeable(qreal x, qreal y, const QColor &color)
    : QGraphicsPolygonItem({}, nullptr), originX(x), originY(y)
{
    this->setBrush(QBrush(color));

    this->setFlag(ItemIsFocusable);
    this->setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);
}


void NodeShapeable::setColors(const QColor &color) {
    this->setBrush(color);
}

void NodeShapeable::activateColors() {
    if (this->brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setPen(QPen(Qt::white));
    } else {
        setPen(QPen(Qt::black));
    }
}
