#include "hexagon.h"

Hexagon::Hexagon(qreal x, qreal y, QBrush brush,  QString text)
    : NodeShapeable(x, y, brush, text)

{
    this->drawShape();
}

void Hexagon::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(midX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY)
                               << QPointF(midX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY)
                               ));

}
