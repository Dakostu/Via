#ifndef OCTAGON_H
#define OCTAGON_H

#include "../interfaces/routenodeshape.h"

namespace Via::Shapes {

class Octagon : public RouteNodeShape
{
    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Octagon(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}

#endif // OCTAGON_H
