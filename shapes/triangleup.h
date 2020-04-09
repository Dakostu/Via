#ifndef TRIANGLEUP_H
#define TRIANGLEUP_H

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
#endif // TRIANGLEUP_H
