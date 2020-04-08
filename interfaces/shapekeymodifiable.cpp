#include "shapekeymodifiable.h"

using namespace Via::Interfaces;

char ShapeKeyModifiable::getShapeKey() const {
    return shapeKey;
}

void ShapeKeyModifiable::setShapeKey(char newStyle) {
    shapeKey = newStyle;
}
