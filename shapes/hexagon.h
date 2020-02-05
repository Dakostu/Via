#ifndef HEXAGON_H
#define HEXAGON_H

#include "../interfaces/nodeshapeable.h"

class Hexagon : public NodeShapeable
{
    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Hexagon(qreal x, qreal y, const QColor &color);

    void drawShape() override;
};

#endif // HEXAGON_H
