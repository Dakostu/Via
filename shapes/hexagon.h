#ifndef NODESHAPETRIANGLE_H
#define NODESHAPETRIANGLE_H

#include "../interfaces/nodeshapeable.h"

class Hexagon : public NodeShapeable
{
    static constexpr qreal SIZE_QUOTIENT = 2.0;
public:
    Hexagon(qreal x, qreal y, QBrush brush, QPen pen, QString text);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLE_H
