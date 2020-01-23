#include "viewcustomizable.h"
#include <QBrush>

ViewCustomizable::ViewCustomizable() : elementSize{1}
{    
}

qreal ViewCustomizable::getElementSize() {
    return elementSize;
}

void ViewCustomizable::setElementSize(qreal newSize) {
    elementSize = newSize;
}

qreal ViewCustomizable::sizeMultiplier(qreal val) {
    return val * elementSize;
}

