#ifndef DIAMOND_H
#define DIAMOND_H

#include "routenodeshape.h"

namespace Via::Shapes {

class Diamond : public RouteNodeShape
{
    static constexpr qreal HEIGHT_MULTIPLICATOR = 1.3;
    static constexpr qreal WIDTH_MULTIPLICATOR = 1.1;
public:
    Diamond(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() const override;
};

}
#endif // DIAMOND_H
