#include "routeextratextlabel.h"
#include <QPen>

RouteExtraTextLabel::RouteExtraTextLabel(QString text)
    : QGraphicsSimpleTextItem(text)
{
   setFlag(ItemIsMovable);
   setDefaultColors();
}


void RouteExtraTextLabel::setSize(qreal newSize) {

}

void RouteExtraTextLabel::setColors(const QColor &color) {
    auto extraTextPen = QPen(color);
    extraTextPen.setWidthF(size);
    setPen(extraTextPen);

}

void RouteExtraTextLabel::setDefaultColors() {
    if (this->brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setColors(Qt::white);
    } else {
        setColors(Qt::black);
    }

}
