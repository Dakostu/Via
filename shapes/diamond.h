#ifndef DIAMOND_H
#define DIAMOND_H

#include "../interfaces/nodeshapeable.h"

namespace Via::Shapes {

class Diamond : public Via::Interfaces::NodeShapeable
{
    static constexpr qreal SIZE_QUOTIENT = 1.2;
public:
    Diamond(qreal x, qreal y, const QColor &color);

    void drawShape() override;
};

}
#endif // DIAMOND_H
