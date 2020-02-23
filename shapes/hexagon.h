#ifndef HEXAGON_H
#define HEXAGON_H

#include "../interfaces/nodeshapeable.h"

namespace Via::Shapes {

class Hexagon : public Via::Interfaces::NodeShapeable
{
    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Hexagon(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}

#endif // HEXAGON_H
