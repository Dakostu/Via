#include "triangledown.h"
#include "shapekeys.h"

using namespace Via::Shapes;

TriangleDown::TriangleDown(qreal x, qreal y, const QColor &color)
    : NodeShapeable(x, y, color)

{
    this->drawShape();
}

void TriangleDown::drawShape() {

    this->setPolygon(QPolygonF(QVector<QPointF>()
                               << QPointF(originX, originY + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX + DEFAULT_LENGTH + sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               << QPointF(originX - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH),
                                          originY - DEFAULT_LENGTH - sizeMultiplier(DEFAULT_EXTRA_LENGTH))
                               ));

}

char TriangleDown::getShapeKey() {
    return TRIANGLE_DOWN_KEY;
}
