#ifndef SQUARE_H
#define SQUARE_H

#include "../interfaces/nodeshapeable.h"

class Square : public NodeShapeable
{
public:
    Square(qreal x, qreal y, const QColor &color);

    void drawShape() override;
};

#endif // SQUARE_H
