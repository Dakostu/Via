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
                               << QPointF(midX + DEFAULT_LENGTH/1.2 + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY)
                               << QPointF(midX,
                                          midY - DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH/1.2 + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY)
                               ));

}
