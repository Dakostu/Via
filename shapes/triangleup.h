#ifndef NODESHAPETRIANGLEUP_H
#define NODESHAPETRIANGLEUP_H

#include "routenodeshape.h"

namespace Via::Shapes {

class TriangleUp : public RouteNodeShape
{
public:
    TriangleUp(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}
#endif // NODESHAPETRIANGLEUP_H
