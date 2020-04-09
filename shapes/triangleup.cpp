#include "triangleup.h"
#include "shapekeys.h"

using namespace Via::Shapes;

TriangleUp::TriangleUp(const QPointF &point, const QColor &color)
    : Triangle(point, color, 0.0, 2.0)

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

char TriangleUp::getShapeKey() const {
    return TRIANGLE_UP_KEY;
}
