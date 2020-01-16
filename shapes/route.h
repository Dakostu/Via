#ifndef ROUTE_H
#define ROUTE_H

//#include "routenode.h"
#include "../interfaces/viewcustomizable.h"
#include "routenode.h"
#include "routeconnection.h"
#include <QLinkedList>
#include <QGraphicsScene>
#include <list>

class Route : public ViewCustomizable
{
protected:
    bool showDirection;
    QColor routeColor;
    QGraphicsScene *currentScene;

    std::list<RouteNode*> nodes;
    std::list<RouteConnection*> connections;
public:
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    Route(const QColor &color, QGraphicsScene *scene);

    virtual void addNode(qreal x, qreal y);
};

#endif // ROUTE_H
