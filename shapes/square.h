#ifndef SQUARE_H
#define SQUARE_H

#include "routenodeshape.h"

namespace Via::Shapes {

class Square : public RouteNodeShape
{
public:
    Square(const QPointF &point, const QColor &color);

    void drawShape() override;
    char getShapeKey() const override;
};

}

#endif // SQUARE_H
