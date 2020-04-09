#include "triangledown.h"
#include "shapekeys.h"

using namespace Via::Shapes;

TriangleDown::TriangleDown(const QPointF &point, const QColor &color)
    : Triangle(point, color, 0.0, -3.5)

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

char TriangleDown::getShapeKey() const {
    return TRIANGLE_DOWN_KEY;
}
