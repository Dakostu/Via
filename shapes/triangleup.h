#ifndef NODESHAPETRIANGLEUP_H
#define NODESHAPETRIANGLEUP_H

#include "../interfaces/nodeshapeable.h"

class TriangleUp : public NodeShapeable
{
public:
    TriangleUp(qreal x, qreal y, const QColor &color);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLEUP_H
