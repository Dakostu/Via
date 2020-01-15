#ifndef NODESHAPETRIANGLE_H
#define NODESHAPETRIANGLE_H

#include "../interfaces/nodeshapeable.h"

class Diamond : public NodeShapeable
{
    static constexpr qreal SIZE_QUOTIENT = 1.2;
public:
    Diamond(qreal x, qreal y, QBrush brush,  QString text);

    virtual void drawShape() override;
};

#endif // NODESHAPETRIANGLE_H
