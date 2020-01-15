#ifndef NODESHAPETRIANGLE_H
#define NODESHAPETRIANGLE_H

#include "../interfaces/nodeshapeable.h"

class TriangleDown : public NodeShapeable
{
public:
    TriangleDown(qreal x, qreal y, QBrush brush, QPen pen, QString text);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLE_H
