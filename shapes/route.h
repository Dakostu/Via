#ifndef ROUTE_H
#define ROUTE_H

#include "../data-structures/indexlist.h"
#include "../controller/uistate.h"
#include "../interfaces/viewcustomizable.h"
#include "routenode.h"
#include "routeconnection.h"
#include <QLinkedList>
#include <QGraphicsScene>

class UIState;
class RouteNode;

class Route : public ViewCustomizable
{
protected:
    bool showDirection;
    QColor routeColor;
    QGraphicsScene *currentScene;
    std::unique_ptr<UIState> &currentState;

    IndexList<RouteNode*> nodes;
public:
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    Route(const QColor &color, QGraphicsScene *scene, std::unique_ptr<UIState> &state);

    virtual void addNode(qreal x, qreal y);
    virtual void setElementSize(int newSize) override;
};

#endif // ROUTE_H
