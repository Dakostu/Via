#ifndef NODESHAPETRIANGLE_H
#define NODESHAPETRIANGLE_H

#include "../interfaces/nodeshapeable.h"

class Square : public NodeShapeable
{
public:
    Square(qreal x, qreal y, const QColor &color);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLE_H
