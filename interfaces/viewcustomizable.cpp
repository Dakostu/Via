#include "viewcustomizable.h"
#include <QBrush>

ViewCustomizable::ViewCustomizable() : elementSize{1}
{    
}

int ViewCustomizable::getElementSize() {
    return elementSize;
}

void ViewCustomizable::setElementSize(int newSize) {
    elementSize = newSize;
}

qreal ViewCustomizable::sizeMultiplier(qreal val) {
    return val * elementSize;
}

