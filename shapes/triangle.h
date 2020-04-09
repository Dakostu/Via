#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "routenodeshape.h"

namespace Via::Shapes {

class Triangle : public RouteNodeShape
{
protected:

    const qreal OFFSET_X;
    const qreal OFFSET_Y;

public:
    Triangle(const QPointF point, const QColor &color, qreal offsetX, qreal offsetY);

    QPointF getCenter() override;
};

}
#endif // TRIANGLE_H
