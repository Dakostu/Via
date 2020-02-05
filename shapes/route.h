#ifndef ROUTE_H
#define ROUTE_H

#include "../data-structures/indexlist.h"
#include "../controller/uistate.h"
#include "../interfaces/viewcustomizable.h"
#include "../model/routenodedata.h"
#include "routenode.h"
#include "routeconnection.h"
#include <QLinkedList>
#include <QGraphicsScene>

class UIState;
class RouteNode;

class Route : public ViewCustomizable
{
protected:
    static constexpr qreal TEMPORARY_NODE_OPACITY = 0.5;

    bool showDirection;
    QColor routeColor;
    QGraphicsScene *currentScene;
    std::unique_ptr<UIState> &currentState;

    IndexList<RouteNode*> nodes;
public:
    Route(const QColor &color, QGraphicsScene *scene, std::unique_ptr<UIState> &state);

    virtual QColor getColors() const;

    virtual void setColors(const QColor &color) override;
    virtual void activateColors() override;

    virtual void addNode(const RouteNodeData &node);
    virtual void addNode(qreal x, qreal y);
    virtual void addTemporaryPreviewNode(qreal x, qreal y);
    virtual void eraseNode(int index);
    virtual void eraseAllNodes();
    virtual void swapNodes(int x, int y);
    virtual void setElementSize(int newSize) override;
};

#endif // ROUTE_H
