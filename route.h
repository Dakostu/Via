#ifndef ROUTE_H
#define ROUTE_H

#include "routenode.h"
#include "viewcustomizable.h"
#include <QList>

class Route : public ViewCustomizable
{
    bool showDirection;
    QList<RouteNode> nodes;
public:
    Route();
};

#endif // ROUTE_H
