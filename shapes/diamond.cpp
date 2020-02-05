#include "diamond.h"

using namespace Via::Shapes;

Diamond::Diamond(qreal x, qreal y, const QColor &color)
    : NodeShapeable(x, y, color)

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
