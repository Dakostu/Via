#ifndef NODESHAPETRIANGLEUP_H
#define NODESHAPETRIANGLEUP_H

#include "../interfaces/routenodeshape.h"

namespace Via::Shapes {

class TriangleUp : public RouteNodeShape
{
public:
    TriangleUp(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}
#endif // NODESHAPETRIANGLEUP_H
