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
                                          originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          originY)
                               << QPointF(originX,
                                          originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          originY)
                               ));

}

char Diamond::getShapeKey() {
    return DIAMOND_KEY;
}
