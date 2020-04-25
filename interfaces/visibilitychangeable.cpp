#include "visibilitychangeable.h"

using namespace Via::Interfaces;

VisibilityChangeable::VisibilityChangeable() : visible(true) {

}

bool VisibilityChangeable::isCurrentlyVisible() const
{
    return visible;
}

void VisibilityChangeable::setVisible(bool isVisible)
{
    visible = isVisible;
}
