#ifndef SHAPEABLE_H
#define SHAPEABLE_H

namespace Via::Interfaces {

class ShapeKeyable {

protected:
    ShapeKeyable() = default;

public:
    virtual ~ShapeKeyable() = default;

    virtual char getShapeKey() const = 0;    

};

}

#endif // SHAPEABLE_H
