#include "colorgenerator.h"
#include <QRandomGenerator>
#include <QRgb>

QColor ColorGenerator::operator()() {
    if (!lastColor.isValid()) {
        lastColor = QColor::fromRgb(QRandomGenerator::global()->generate());
    } else {
        qreal h, s, v;
        lastColor.getHsvF(&h, &s, &v);

        h += GOLDEN_RATIO + (QRandomGenerator::global()->bounded(100)/1000.0 - 0.5);

        if (h > 1.0) {
            h -= 1.0;
        }
        if (QRandomGenerator::global()->bounded(256) & 1) {
            s = std::min(0.65, s + 0.05);
            v = std::max(0.35, v - 0.05);
        } else {
            s = std::max(0.35, s - 0.05);
            v = std::min(0.65, v + 0.05);
        }


        lastColor = QColor::fromHsvF(h,s,v);
    }

    return lastColor;
}
