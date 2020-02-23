#include "octagon.h"
#include "shapekeys.h"

using namespace Via::Shapes;

Octagon::Octagon(qreal x, qreal y, const QColor &color)
    : NodeShapeable(x, y, color)

{
    this->drawShape();
}

void Octagon::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(originX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               << QPointF(originX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               << QPointF(originX + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT,
                                          originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY - DEFAULT_LENGTH/SIZE_QUOTIENT - sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               << QPointF(originX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY + DEFAULT_LENGTH/SIZE_QUOTIENT + sizeMultiplier(DEFAULT_EXTRA_LENGTH)/SIZE_QUOTIENT)
                               ));

}

char Octagon::getShapeKey() {
    return OCTAGON_KEY;
}
