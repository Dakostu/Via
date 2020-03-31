#include "routeextratextlabel.h"
#include <QDebug>
#include <QFont>
#include <QRectF>

using namespace Via::UI;
using namespace Via::Shapes;

RouteExtraTextLabel::RouteExtraTextLabel(const QString &text, RouteNodeShape *parent)
    : QGraphicsSimpleTextItem(text), parentNode(parent)
{
   setFlag(ItemIsMovable);
   activateColors();
   this->acceptHoverEvents();
}


void RouteExtraTextLabel::setElementSize(int newSize) {
    ViewCustomizable::setElementSize(newSize);
    auto font = this->font();
    font.setPointSizeF(elementSize / 2 + 7);
    this->setFont(font);
}

void RouteExtraTextLabel::setColors(const QColor &color) {
    setBrush(color);
}

void RouteExtraTextLabel::activateColors() {
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
    activateColors();
    QGraphicsSimpleTextItem::hoverLeaveEvent(hoverEvent);
}

void RouteExtraTextLabel::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsSimpleTextItem::mouseMoveEvent(event);

}
