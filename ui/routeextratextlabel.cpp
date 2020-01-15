#include "routeextratextlabel.h"
#include <QDebug>
#include <QFont>
#include <QRectF>

RouteExtraTextLabel::RouteExtraTextLabel(QString text, NodeShapeable *parent)
    : QGraphicsSimpleTextItem(text), parentNode(parent)
{
   setFlag(ItemIsMovable);
   setDefaultColors();
   this->acceptHoverEvents();
}


void RouteExtraTextLabel::setSize(qreal newSize) {
    ViewCustomizable::setSize(newSize);
    auto font = this->font();
    font.setPointSizeF(size / 2 + 7);
    this->setFont(font);
}

void RouteExtraTextLabel::setColors(const QColor &color) {
    setBrush(color);
}

void RouteExtraTextLabel::setDefaultColors() {
    if (this->brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setColors(Qt::white);
    } else {
        setColors(Qt::black);
    }

}

void RouteExtraTextLabel::hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) {
    this->setColors(~this->brush().color().rgb());
    QGraphicsSimpleTextItem::hoverEnterEvent(hoverEvent);
}

void RouteExtraTextLabel::hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) {
    setDefaultColors();
    QGraphicsSimpleTextItem::hoverLeaveEvent(hoverEvent);
}

void RouteExtraTextLabel::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsSimpleTextItem::mouseMoveEvent(event);

}
