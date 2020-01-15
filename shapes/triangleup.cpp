#include "triangleup.h"

TriangleUp::TriangleUp(qreal x, qreal y, QBrush brush, QString text)
    : NodeShapeable(x, y, brush, text)

{
    this->drawShape();
}

void TriangleUp::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(midX, midY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(midX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          midY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               ));

}
