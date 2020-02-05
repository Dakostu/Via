#ifndef OCTAGON_H
#define OCTAGON_H

#include "../interfaces/nodeshapeable.h"

class Octagon : public NodeShapeable
{

    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Octagon(qreal x, qreal y, const QColor &color);

    void drawShape() override;
};

#endif // OCTAGON_H
