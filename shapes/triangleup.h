#ifndef NODESHAPETRIANGLE_H
#define NODESHAPETRIANGLE_H

#include "../interfaces/nodeshapeable.h"

class TriangleUp : public NodeShapeable
{
public:
    TriangleUp(qreal x, qreal y, QBrush brush);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLE_H