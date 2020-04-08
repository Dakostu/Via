#ifndef SHAPEKEYMODIFIABLE_H
#define SHAPEKEYMODIFIABLE_H

#include "shapekeyable.h"

namespace Via::Interfaces {

class ShapeKeyModifiable : public ShapeKeyable
{
protected:
    ShapeKeyModifiable() = default;
    char shapeKey;

public:
    char getShapeKey() const override;
    virtual void setShapeKey(char newStyle);
};

}

#endif // SHAPEKEYMODIFIABLE_H
