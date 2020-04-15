#ifndef VISIBILITYCHANGEABLE_H
#define VISIBILITYCHANGEABLE_H

namespace Via::Interfaces {

class VisibilityChangeable
{
protected:
    bool visible;

public:
    VisibilityChangeable() = default;
    virtual bool isVisible() const;
    virtual void setVisible(bool value);
};

}
#endif // VISIBILITYCHANGEABLE_H
