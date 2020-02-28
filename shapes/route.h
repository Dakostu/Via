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
    char style;
    RouteNodeShapeFactory nodeShapeFactory;
    QGraphicsScene *currentScene;
    std::unique_ptr<Via::Control::RouteNodeState> &currentState;

    Via::Structures::IndexList<RouteNode*> nodes;
public:
    Route(const QColor &color, const QString &selectedStyle, QGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state);
    Route(const QColor &color, char selectedStyle, QGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state);

    virtual QColor getColors() const;

    void setColors(const QColor &color) override;
    void activateColors() override;

    void addNode(const Via::Model::RouteNodeData &node);
    void addNode(qreal x, qreal y);
    void addTemporaryPreviewNode(qreal x, qreal y);
    void removeTemporaryPreviewNode();
    bool hasTemporaryPreviewNode();
    void eraseNode(int index);
    void eraseAllNodes();
    void swapNodes(int node1, int node2);
    void setElementSize(int newSize) override;
    void setStyleOfNode(int routeNodeIndex, char newStyle);
    void setStyleOfNode(int routeNodeIndex, const QString &newStyle);
    char getStyle() const;
    void setStyle(const QString &newStyle);
    void setStyle(char newStyle);

    const RouteNode& operator[](int nodeIndex);
};

}
#endif // ROUTE_H
