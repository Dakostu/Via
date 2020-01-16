#ifndef ROUTE_H
#define ROUTE_H

//#include "routenode.h"
#include "../interfaces/viewcustomizable.h"
#include "routenode.h"
#include <QLinkedList>

class Route : public ViewCustomizable
{
    bool showDirection;
    QColor routeColor;
    QLinkedList<RouteNode> nodes;
public:
    Route();
};

#endif // ROUTE_H
