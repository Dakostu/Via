#ifndef ROUTENODE_H
#define ROUTENODE_H

#include "../interfaces/nodeshapeable.h"
#include "../interfaces/viewcustomizable.h"
#include "../ui/routenodelabel.h"
#include "../ui/routeextratextlabel.h"
#include "routeconnection.h"
#include <QObject>
#include <QGraphicsItemGroup>
#include <memory>

using ConnectionVector = std::vector<std::unique_ptr<RouteConnection>>;

class RouteNode : public QGraphicsItemGroup, public ViewCustomizable
{

protected:
    std::unique_ptr<NodeShapeable> node;
    RouteNodeLabel nodeLabel;
    RouteExtraTextLabel extraTextLabel;
    bool styleDiffersFromRoute;
    ConnectionVector fromConnections;
    ConnectionVector toConnections;

    void centerNodeLabelBox();    


public:
    RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText);
    RouteNode(NodeShapeable *newNode, QString nodeLabelText);

    virtual void setSize(qreal newSize) override;
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

    virtual void setOpacity(qreal opacity);
    virtual void setNodeLabelOpacity(qreal opacity);
    bool isInvisible();

    ConnectionVector* getToConnections();
    RouteExtraTextLabel* getExtraText();
    void connect(RouteNode &from);

};

#endif // ROUTENODE_H
