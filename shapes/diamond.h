#ifndef DIAMOND_H
#define DIAMOND_H

#include "routenodeshape.h"

namespace Via::Shapes {

class Diamond : public RouteNodeShape
{
    static constexpr qreal SIZE_QUOTIENT = 1.2;
public:
    Diamond(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}
#endif // DIAMOND_H
