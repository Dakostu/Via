#ifndef ROUTENODE_H
#define ROUTENODE_H

#include "../controller/states/routenodestate.h"
#include "../interfaces/viewcustomizable.h"
#include "../ui/routenodelabel.h"
#include "../ui/routeextratextlabel.h"
#include "routeconnection.h"
#include "routenodeshape.h"
#include <QObject>
#include <QString>
#include <QGraphicsItemGroup>
#include <memory>

namespace Via::Control {
    class UIState;
}

namespace Via::Shapes {

class RouteNode : public QGraphicsItemGroup, public Via::Interfaces::ViewCustomizable
{

protected:
    std::unique_ptr<RouteNodeShape> node;
    Via::UI::RouteNodeLabel nodeLabel;
    Via::UI::RouteExtraTextLabel extraTextLabel;
    QString style;
    bool styleDiffersFromRoute;
    RouteConnection* fromConnection;
    std::unique_ptr<RouteConnection> toConnection;
    std::unique_ptr<Via::Control::RouteNodeState> &currentState;

    void centerNodeLabelBox();    


public:
    RouteNode(RouteNodeShape *newNode, QString nodeLabelText, QString extraTextLabelText, std::unique_ptr<Via::Control::RouteNodeState> &state);
    RouteNode(RouteNodeShape *newNode, QString nodeLabelText, std::unique_ptr<Via::Control::RouteNodeState> &state);


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
    virtual void setShape(RouteNodeShape* newShape, const QString &newStyle);
    void setStyleDiffersFromRoute(bool value);

    virtual void resetFromConnection();
    virtual void resetToConnection();

    QColor getColor() const;
    RouteConnection* getFromConnection();
    RouteConnection* getToConnection();
    Via::UI::RouteExtraTextLabel* getExtraText();
    Via::UI::RouteNodeLabel* getNodeLabel();
    RouteNodeShape* getNodeShape() const;
    bool getStyleDiffersFromRoute() const;

    void connect(RouteNode &from);
    void swap(RouteNode *with);
    void moveBy(qreal dx, qreal dy);
    QPointF getCenter();
    void updateRouteConnections();

};

}
#endif // ROUTENODE_H
