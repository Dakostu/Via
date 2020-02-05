#include "routenodelabel.h"
#include <QBrush>
#include <QFont>

using namespace Via::UI;

RouteNodeLabel::RouteNodeLabel(QString text)
    : QGraphicsSimpleTextItem(text)
{
    activateColors();
}

void RouteNodeLabel::setElementSize(int newSize) {
    ViewCustomizable::setElementSize(newSize);
    auto font = this->font();
    font.setPointSizeF(elementSize / 2 + 7);
    this->setFont(font);
}


void RouteNodeLabel::setColors(const QColor &color) {
    setBrush(color);
}

void RouteNodeLabel::activateColors() {
    if (this->brush().color().lightnessF() < FILLCOLOR_LIGHTNESS_THRESHOLD) {
        setColors(Qt::white);
    } else {
        setColors(Qt::black);
    }
}
