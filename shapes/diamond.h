#ifndef DIAMOND_H
#define DIAMOND_H

#include "../interfaces/routenodeshape.h"

namespace Via::Shapes {

class Diamond : public Via::Interfaces::RouteNodeShape
{
    static constexpr qreal SIZE_QUOTIENT = 1.2;
public:
    Diamond(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}
#endif // DIAMOND_H
