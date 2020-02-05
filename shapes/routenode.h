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

class RouteNode : public QGraphicsItemGroup, public ViewCustomizable
{

protected:
    std::unique_ptr<NodeShapeable> node;
    RouteNodeLabel nodeLabel;
    RouteExtraTextLabel extraTextLabel;
    bool styleDiffersFromRoute;
    RouteConnection* fromConnection;
    std::unique_ptr<RouteConnection> toConnection;
    std::unique_ptr<UIState> &currentState;

    void centerNodeLabelBox();    


public:
    RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText, std::unique_ptr<UIState> &state);
    RouteNode(NodeShapeable *newNode, QString nodeLabelText, std::unique_ptr<UIState> &state);

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;
    void activateColors() override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void triggerParentMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

    virtual void setNodeOutlineColor(const QColor &color);
    virtual void setOpacity(qreal opacity);
    virtual void setNodeLabelOpacity(qreal opacity);
    virtual void setNodeLabelText(const QString &newText);
    virtual void resetFromConnection();
    virtual void resetToConnection();

    QColor getColor() const;
    RouteConnection* getFromConnection();
    RouteConnection* getToConnection();
    RouteExtraTextLabel* getExtraText();
    RouteNodeLabel* getNodeLabel();

    void connect(RouteNode &from);
    void swap(RouteNode *with);
    void moveBy(qreal dx, qreal dy);
    QPointF getCenter();
    void updateRouteConnections();

    bool getStyleDiffersFromRoute() const;
    void setStyleDiffersFromRoute(bool value);
};

#endif // ROUTENODE_H
