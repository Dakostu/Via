#ifndef ROUTE_H
#define ROUTE_H

#include "../data-structures/indexlist.h"
#include "../controller/states/routenodestate.h"
#include "../interfaces/viewcustomizable.h"
#include "../model/routenodedata.h"
#include "routenode.h"
#include "routeconnection.h"
#include "routenodeshapefactory.h"
#include <QLinkedList>
#include <QGraphicsScene>

namespace Via::Control {
class UIState;
}

namespace Via::Shapes {


class Route : public Via::Interfaces::ViewCustomizable
{
protected:
    static constexpr qreal TEMPORARY_NODE_OPACITY = 0.5;

    bool showDirection;
    QColor routeColor;
    QString style;
    RouteNodeShapeFactory nodeShapeFactory;
    QGraphicsScene *currentScene;
    std::unique_ptr<Via::Control::RouteNodeState> &currentState;

    Via::Structures::IndexList<RouteNode*> nodes;
public:
    Route(const QColor &color, const QString &selectedStyle, QGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state);

    virtual QColor getColors() const;

    void setColors(const QColor &color) override;
    void activateColors() override;

    virtual void addNode(const Via::Model::RouteNodeData &node);
    virtual void addNode(qreal x, qreal y);
    virtual void addTemporaryPreviewNode(qreal x, qreal y);
    virtual void removeTemporaryPreviewNode();
    virtual bool hasTemporaryPreviewNode();
    virtual void eraseNode(int index);
    virtual void eraseAllNodes();
    virtual void swapNodes(int node1, int node2);
    virtual void setElementSize(int newSize) override;
    QString getStyle() const;
    void setStyle(const QString &value);
};

}
#endif // ROUTE_H
