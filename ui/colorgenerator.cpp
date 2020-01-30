#include "colorgenerator.h"
#include <QRandomGenerator>
#include <QRgb>


QColor ColorGenerator::operator()() {
    if (!lastColor.isValid()) {
        lastColor = QColor::fromRgb(QRandomGenerator::global()->generate());
    } else {
        qreal h, s, v;
        lastColor.getHsvF(&h, &s, &v);

        h += GOLDEN_RATIO;
        if (h > 1.0) {
            h -= 1.0;
            s = std::min(1.0, s + 0.1);
            v = std::max(0.0, v - 0.1);
        } else {
            s = std::max(0.0, s - 0.1);
            v = std::min(1.0, v + 0.1);
        }

        lastColor = QColor::fromHsvF(h,s,v);
    }

    return lastColor;
}
