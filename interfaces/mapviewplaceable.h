#ifndef MAPVIEWPLACEABLE_H
#define MAPVIEWPLACEABLE_H

#include "nameable.h"
#include "viewcustomizable.h"
#include "visibilitychangeable.h"

namespace Via::Interfaces {

class MapViewPlaceable :
        public ViewCustomizable,
        public Nameable,
        public VisibilityChangeable {

protected:
    MapViewPlaceable() = default;

};


}

#endif // MAPVIEWPLACEABLE_H
