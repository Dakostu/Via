#include "triangleup.h"
#include "shapekeys.h"

using namespace Via::Shapes;

TriangleUp::TriangleUp(qreal x, qreal y, const QColor &color)
    : NodeShapeable(x, y, color)

{
    this->drawShape();
}

void TriangleUp::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(originX, originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               ));

}

char TriangleUp::getShapeKey() {
    return TRIANGLE_UP_KEY;
}
