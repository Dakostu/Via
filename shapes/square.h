#ifndef SQUARE_H
#define SQUARE_H

#include "../interfaces/routenodeshape.h"

namespace Via::Shapes {

class Square : public RouteNodeShape
{
public:
    Square(qreal x, qreal y, const QColor &color);

    void drawShape() override;
    char getShapeKey() override;
};

}

#endif // SQUARE_H
