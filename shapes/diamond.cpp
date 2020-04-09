#include "diamond.h"
#include "shapekeys.h"

using namespace Via::Shapes;

Diamond::Diamond(const QPointF &point, const QColor &color)
    : RouteNodeShape(point, color)

{
    this->drawShape();
}

void Diamond::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(originX,
                                          originY + DEFAULT_LENGTH * HEIGHT_MULTIPLICATOR + sizeMultiplier(DEFAULT_EXTRA_LENGTH) * HEIGHT_MULTIPLICATOR)
                               << QPointF(originX + DEFAULT_LENGTH * WIDTH_MULTIPLICATOR+ sizeMultiplier(DEFAULT_EXTRA_LENGTH) * WIDTH_MULTIPLICATOR,
                                          originY)
                               << QPointF(originX,
                                          originY - DEFAULT_LENGTH * HEIGHT_MULTIPLICATOR - sizeMultiplier(DEFAULT_EXTRA_LENGTH) * HEIGHT_MULTIPLICATOR)
                               << QPointF(originX - DEFAULT_LENGTH * WIDTH_MULTIPLICATOR - sizeMultiplier(DEFAULT_EXTRA_LENGTH) * WIDTH_MULTIPLICATOR,
                                          originY)
                               ));

}

char Diamond::getShapeKey() const {
    return DIAMOND_KEY;
}
