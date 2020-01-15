#ifndef NODESHAPETRIANGLE_H
#define NODESHAPETRIANGLE_H

#include "../interfaces/nodeshapeable.h"

class Square : public NodeShapeable
{
public:
    Square(qreal x, qreal y, QBrush brush,  QString text);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLE_H
