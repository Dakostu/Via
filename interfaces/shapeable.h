#ifndef SHAPEABLE_H
#define SHAPEABLE_H

namespace Via::Interfaces {

class Shapeable {

protected:
    Shapeable() = default;

public:
    virtual ~Shapeable() = default;

    virtual char getShapeKey() const = 0;
    virtual void setShapeKey(char newStyle) = 0;

};

}

#endif // SHAPEABLE_H
