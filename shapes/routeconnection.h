#ifndef ROUTECONNECTION_H
#define ROUTECONNECTION_H

#include "../interfaces/viewcustomizable.h"
#include <QGraphicsItemGroup>

class RouteConnection : public QGraphicsItemGroup, public ViewCustomizable
{
public:
    RouteConnection();
};

#endif // ROUTECONNECTION_H
