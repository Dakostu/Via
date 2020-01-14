#ifndef ROUTENODE_H
#define ROUTENODE_H

#include "../interfaces/viewcustomizable.h"
#include <QObject>

class RouteNode : public ViewCustomizable
{
    qint64 x;
    qint64 y;

    bool hasDifferentStyle;
    bool invisible;
public:
    RouteNode();
};

#endif // ROUTENODE_H
