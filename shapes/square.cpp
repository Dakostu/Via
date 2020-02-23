#include "square.h"
#include "shapekeys.h"

using namespace Via::Shapes;

Square::Square(qreal x, qreal y, const QColor &color)
    : NodeShapeable(x, y, color)

{
    this->drawShape();
}

void Square::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(originX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               ));

}

char Square::getShapeKey() {
    return SQUARE_KEY;
}
