#ifndef COLORGENERATOR_H
#define COLORGENERATOR_H

#include <QColor>


class ColorGenerator
{
    static constexpr qreal GOLDEN_RATIO = 0.618033988749895;
    QColor lastColor;

public:
    QColor operator()();
};

#endif // COLORGENERATOR_H
