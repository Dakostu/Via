#ifndef NODESHAPETRIANGLEDOWN_H
#define NODESHAPETRIANGLEDOWN_H

#include "../interfaces/nodeshapeable.h"

class TriangleDown : public NodeShapeable
{
public:
    TriangleDown(qreal x, qreal y, const QColor &color);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLEDOWN_H
