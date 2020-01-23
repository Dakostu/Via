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
public:
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    Route(const QColor &color, QGraphicsScene *scene);

    virtual void addNode(qreal x, qreal y);
    virtual void setElementSize(qreal newSize) override;
};

#endif // ROUTE_H
