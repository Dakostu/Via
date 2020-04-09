#ifndef NODESHAPETRIANGLEDOWN_H
#define NODESHAPETRIANGLEDOWN_H

#include "triangle.h"

namespace Via::Shapes {

class TriangleDown : public Triangle
{
public:
    TriangleDown(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() const override;    
};

}
#endif // NODESHAPETRIANGLEDOWN_H
