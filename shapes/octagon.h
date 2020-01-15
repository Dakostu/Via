#ifndef NODESHAPETRIANGLE_H
#define NODESHAPETRIANGLE_H

#include "../interfaces/nodeshapeable.h"

class Octagon : public NodeShapeable
{

    static constexpr qreal SIZE_QUOTIENT = 2;
public:
    Octagon(qreal x, qreal y, QBrush brush, QPen pen, QString text);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLE_H
