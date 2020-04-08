#ifndef HEXAGON_H
#define HEXAGON_H

#include "routenodeshape.h"

namespace Via::Shapes {

class Hexagon : public RouteNodeShape
{
    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Hexagon(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() const override;
};

}

#endif // HEXAGON_H
