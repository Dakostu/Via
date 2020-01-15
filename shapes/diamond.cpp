#include "diamond.h"

Diamond::Diamond(qreal x, qreal y, QBrush brush, QPen pen, QString text)
    : NodeShapeable(x, y, brush, pen, text)

{
    this->drawShape();
}

void Diamond::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(midX,
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY)
                               << QPointF(midX,
                                          midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY)
                               ));

}
