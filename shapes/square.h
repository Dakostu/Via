#ifndef SQUARE_H
#define SQUARE_H

#include "../interfaces/nodeshapeable.h"

namespace Via::Shapes {

class Square : public Via::Interfaces::NodeShapeable
{
public:
    Square(qreal x, qreal y, const QColor &color);

    void drawShape() override;
};

}

#endif // SQUARE_H
