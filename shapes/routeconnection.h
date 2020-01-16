#ifndef ROUTECONNECTION_H
#define ROUTECONNECTION_H

#include "../interfaces/viewcustomizable.h"
#include "../interfaces/nodeshapeable.h"
#include "routenode.h"
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>

class RouteConnection : public QLineF, public ViewCustomizable
{
    RouteNode *from;
    RouteNode *to;
    QPen defaultPen;
    QPen currentPen;

    //std::unique_ptr<NodeShapeable> midShape;

public:
    RouteConnection(RouteNode *fromNode, RouteNode *toNode, QColor color);

    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void setSize(qreal newSize) override;
    virtual QPen getPen();

};

#endif // ROUTECONNECTION_H
