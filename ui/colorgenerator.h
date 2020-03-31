#ifndef COLORGENERATOR_H
#define COLORGENERATOR_H

#include <QColor>

namespace Via::UI {

class ColorGenerator
{
    static constexpr qreal GOLDEN_RATIO = 0.718033988749895;
    static constexpr qreal H_MAX = 1.0;
    static constexpr qreal HSV_MAX = 0.65;
    static constexpr qreal HSV_MIN = 0.35;
    static constexpr qreal HSV_STEP = 0.05;

    QColor lastColor;

public:
    QColor operator()();
};

}
#endif // COLORGENERATOR_H
