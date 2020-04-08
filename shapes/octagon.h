#ifndef OCTAGON_H
#define OCTAGON_H

#include "routenodeshape.h"

namespace Via::Shapes {

class Octagon : public RouteNodeShape
{
    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Octagon(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() const override;
};

}

#endif // OCTAGON_H
