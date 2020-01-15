#include "viewcustomizable.h"
#include <QBrush>

ViewCustomizable::ViewCustomizable() : size{1}
{    
}

qreal ViewCustomizable::getSize() {
    return size;
}

void ViewCustomizable::setSize(qreal newSize) {
    size = newSize;
}

qreal ViewCustomizable::sizeMultiplier(qreal val) {
    return val * size;
}

