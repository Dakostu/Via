#include "routenodelabel.h"
#include <QBrush>
#include <QFont>

RouteNodeLabel::RouteNodeLabel(QString text)
    : QGraphicsSimpleTextItem(text)
{
    setDefaultColors();
}

void RouteNodeLabel::setSize(qreal newSize) {
    ViewCustomizable::setSize(newSize);
    auto font = this->font();
    font.setPointSizeF(size / 2 + 7);
    this->setFont(font);
}


void RouteNodeLabel::setColors(const QColor &color) {
    setBrush(color);
}

void RouteNodeLabel::setDefaultColors() {
    if (this->brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setColors(Qt::white);
    } else {
        setColors(Qt::black);
    }
}
