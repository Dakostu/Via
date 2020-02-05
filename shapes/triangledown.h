#ifndef NODESHAPETRIANGLEDOWN_H
#define NODESHAPETRIANGLEDOWN_H

#include "../interfaces/nodeshapeable.h"

namespace Via::Shapes {

class TriangleDown : public Via::Interfaces::NodeShapeable
{
public:
    TriangleDown(qreal x, qreal y, const QColor &color);

    void drawShape() override;
};

}
#endif // NODESHAPETRIANGLEDOWN_H
