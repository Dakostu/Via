#ifndef DIAMOND_H
#define DIAMOND_H

#include "../interfaces/nodeshapeable.h"

class Diamond : public NodeShapeable
{
    static constexpr qreal SIZE_QUOTIENT = 1.2;
public:
    Diamond(qreal x, qreal y, const QColor &color);

    virtual void drawShape() override;
};

#endif // DIAMOND_H
