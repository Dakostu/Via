#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../data-structures/indexlist.h"
#include "data.h"

namespace Via::Model {

struct RouteData : public Data
{
    static inline const char* ROUTE_NAME_KEY = "n";
    static inline const char* ROUTE_SIZE_KEY = "s";
    static inline const char* ROUTE_COLOR_KEY = "c";
    static inline const char* ROUTE_SHOW_ORDER_KEY = "o";
    static inline const char* ROUTE_SHAPE_KEY = "p";
    static inline const char* ROUTE_NODES_KEY = "a";

    //void refreshNames(RouteDataIterator&& it, size_t index);


    /*
    void RouteData::refreshNames(RouteDataIterator&& it, size_t index) {
        if (it == nodes.end()) {
            return;
        }

        for (; it != nodes.end(); ++it, ++index) {
            auto &node = *it;
            QString newNumber = QString::number(index + 1);
            if (!node.isNameChangedByUser() && node.getName() != newNumber) {
                node.setName(LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(newNumber));
            }
        }
    } */
};

}

#endif // ROUTEDATA_H
