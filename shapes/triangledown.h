#ifndef NODESHAPETRIANGLEDOWN_H
#define NODESHAPETRIANGLEDOWN_H

#include "../interfaces/routenodeshape.h"

namespace Via::Shapes {

class TriangleDown : public Via::Interfaces::RouteNodeShape
{
public:
    TriangleDown(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}
#endif // NODESHAPETRIANGLEDOWN_H
