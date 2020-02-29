#include "viewcustomizable.h"
#include <QBrush>

using namespace Via::Interfaces;


int ViewCustomizable::getElementSize() const {
    return elementSize;
}

void ViewCustomizable::setElementSize(int newSize) {
    elementSize = newSize;
}

qreal ViewCustomizable::sizeMultiplier(qreal val) {
    return val * elementSize;
}

