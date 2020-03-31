#include "colorgenerator.h"
#include <QRandomGenerator>
#include <QRgb>

using namespace Via::UI;

QColor ColorGenerator::operator()() {
    if (!lastColor.isValid()) {
        lastColor = QColor::fromRgb(QRandomGenerator::global()->generate());
    } else {
        qreal h;
        qreal s;
        qreal v;
        lastColor.getHsvF(&h, &s, &v);

        h += GOLDEN_RATIO + (QRandomGenerator::global()->bounded(100)/1000.0 - 0.5);

        if (h > H_MAX) {
            h -= H_MAX;
        }
        if (QRandomGenerator::global()->bounded(256) & 1) {
            s = std::min(HSV_MAX, s + HSV_STEP);
            v = std::max(HSV_MIN, v - HSV_STEP);
        } else {
            s = std::max(HSV_MIN, s - HSV_STEP);
            v = std::min(HSV_MAX, v + HSV_STEP);
        }


        lastColor = QColor::fromHsvF(h,s,v);
    }

    return lastColor;
}
