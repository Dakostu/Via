#include "visibilitychangeable.h"

using namespace Via::Interfaces;

VisibilityChangeable::VisibilityChangeable() : visible(true) {

}

bool VisibilityChangeable::isVisible() const
{
    return visible;
}

void VisibilityChangeable::setVisible(bool value)
{
    visible = value;
}
