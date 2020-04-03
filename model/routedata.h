#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../interfaces/shapeable.h"
#include "../data-structures/indexlist.h"
#include "data.h"
#include "routenodedata.h"
#include <list>
#include <QStringList>


namespace Via::Model {

using RouteDataIterator = Via::Structures::IndexList<Via::Model::RouteNodeData>::iterator;

struct RouteData : public Data
{
    static inline const char* ROUTE_NAME_KEY = "n";
    static inline const char* ROUTE_SIZE_KEY = "s";
    static inline const char* ROUTE_COLOR_KEY = "c";
    static inline const char* ROUTE_SHOW_ORDER_KEY = "o";
    static inline const char* ROUTE_SHAPE_KEY = "p";
    static inline const char* ROUTE_NODES_KEY = "a";

    //void refreshNames(RouteDataIterator&& it, size_t index);
};

}

#endif // ROUTEDATA_H
