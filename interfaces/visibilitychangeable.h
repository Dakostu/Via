#ifndef VISIBILITYCHANGEABLE_H
#define VISIBILITYCHANGEABLE_H

namespace Via::Interfaces {

class VisibilityChangeable
{
protected:
    bool visible;

public:
    VisibilityChangeable() = default;
    bool isVisible() const;
    void setVisible(bool value);
};

}
#endif // VISIBILITYCHANGEABLE_H
