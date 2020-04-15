#include "visibilitychangeable.h"

using namespace Via::Interfaces;

bool VisibilityChangeable::isVisible() const
{
    return visible;
}

void VisibilityChangeable::setVisible(bool value)
{
    visible = value;
}
