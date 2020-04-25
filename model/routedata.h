#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../data-structures/indexlist.h"
#include "data.h"

namespace Via::Model {

struct RouteData : public Data
{
    static inline const char* ROUTE_NAME_KEY = "n";
    static inline const char* ROUTE_NAME_CHANGED_KEY = "g";
    static inline const char* ROUTE_SIZE_KEY = "s";
    static inline const char* ROUTE_COLOR_KEY = "c";
    static inline const char* ROUTE_SHOW_ORDER_KEY = "o";
    static inline const char* ROUTE_SHAPE_KEY = "p";
    static inline const char* ROUTE_NODES_KEY = "a";
    static inline const char* ROUTE_VISIBLE_KEY = "i";

};

}

#endif // ROUTEDATA_H
