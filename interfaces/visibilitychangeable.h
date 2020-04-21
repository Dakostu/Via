#ifndef VISIBILITYCHANGEABLE_H
#define VISIBILITYCHANGEABLE_H

namespace Via::Interfaces {

class VisibilityChangeable
{
protected:
    bool visible;

    VisibilityChangeable();

public:
    virtual ~VisibilityChangeable() = default;

    virtual bool isVisible() const;
    virtual void setVisible(bool isVisible);
};

}
#endif // VISIBILITYCHANGEABLE_H
