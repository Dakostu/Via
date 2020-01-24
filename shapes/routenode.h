#ifndef ROUTENODE_H
#define ROUTENODE_H

#include "../controller/uistate.h"
#include "../interfaces/nodeshapeable.h"
#include "../interfaces/viewcustomizable.h"
#include "../ui/routenodelabel.h"
#include "../ui/routeextratextlabel.h"
#include "routeconnection.h"
#include <QObject>
#include <QGraphicsItemGroup>
#include <memory>

class UIState;

using ConnectionVector = std::vector<RouteConnection*>;

class RouteNode : public QGraphicsItemGroup, public ViewCustomizable
{

protected:
    std::unique_ptr<NodeShapeable> node;
    RouteNodeLabel nodeLabel;
    RouteExtraTextLabel extraTextLabel;
    bool styleDiffersFromRoute;
    ConnectionVector fromConnections;
    ConnectionVector toConnections;
    std::unique_ptr<UIState> &currentState;

    void centerNodeLabelBox();    


public:
    RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText, std::unique_ptr<UIState> &state);
    RouteNode(NodeShapeable *newNode, QString nodeLabelText, std::unique_ptr<UIState> &state);

    virtual void setElementSize(int newSize) override;
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

    virtual void setOpacity(qreal opacity);
    virtual void setNodeLabelOpacity(qreal opacity);
    bool isInvisible();

    QColor getColor() const;
    ConnectionVector* getToConnections();
    RouteExtraTextLabel* getExtraText();

    void connect(RouteNode &from);

};

#endif // ROUTENODE_H
