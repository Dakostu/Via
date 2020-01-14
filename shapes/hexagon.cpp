#include "hexagon.h"

Hexagon::Hexagon(qreal x, qreal y, QBrush brush, QPen pen, QString text)
    : NodeShapeable(x, y, brush, pen, text)

{
    this->drawShape();
}

void Hexagon::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(midX - DEFAULT_LENGTH/2 - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH/2 + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY)
                               << QPointF(midX + DEFAULT_LENGTH/2 + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH/2 - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY)
                               ));

}
