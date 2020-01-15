#include "octagon.h"

Octagon::Octagon(qreal x, qreal y, QBrush brush, QPen pen, QString text)
    : NodeShapeable(x, y, brush, pen, text)

{
    this->drawShape();
}

void Octagon::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(midX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               << QPointF(midX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               << QPointF(midX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               << QPointF(midX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               ));

}
