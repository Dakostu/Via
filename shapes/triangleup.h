#ifndef NODESHAPETRIANGLEUP_H
#define NODESHAPETRIANGLEUP_H

#include "../interfaces/nodeshapeable.h"

namespace Via::Shapes {

class TriangleUp : public Via::Interfaces::NodeShapeable
{
public:
    TriangleUp(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}
#endif // NODESHAPETRIANGLEUP_H
