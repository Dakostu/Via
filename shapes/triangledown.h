#ifndef NODESHAPETRIANGLEDOWN_H
#define NODESHAPETRIANGLEDOWN_H

#include "routenodeshape.h"

namespace Via::Shapes {

class TriangleDown : public RouteNodeShape
{
public:
    TriangleDown(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() const override;
};

}
#endif // NODESHAPETRIANGLEDOWN_H
