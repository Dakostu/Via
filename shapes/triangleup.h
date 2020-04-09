#ifndef NODESHAPETRIANGLEUP_H
#define NODESHAPETRIANGLEUP_H

#include "triangle.h"

namespace Via::Shapes {

class TriangleUp : public Triangle
{
public:
    TriangleUp(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() const override;
};

}
#endif // NODESHAPETRIANGLEUP_H
