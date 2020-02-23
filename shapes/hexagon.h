#ifndef HEXAGON_H
#define HEXAGON_H

#include "../interfaces/routenodeshape.h"

namespace Via::Shapes {

class Hexagon : public Via::Interfaces::RouteNodeShape
{
    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Hexagon(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}

#endif // HEXAGON_H
