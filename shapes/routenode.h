#ifndef ROUTENODE_H
#define ROUTENODE_H

#include "../controller/states/routenodestate.h"

#include "../interfaces/nameable.h"
#include "../interfaces/serializable.h"
#include "../interfaces/shapekeyable.h"
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

class RouteNode : public QGraphicsItemGroup,
        public Via::Interfaces::ViewCustomizable,
        public Via::Interfaces::Serializable,
        public Via::Interfaces::ShapeKeyable,
        public Via::Interfaces::Nameable
{

protected:
    std::unique_ptr<RouteNodeShape> node;
    Via::UI::RouteNodeLabel nodeLabel;
    Via::UI::RouteExtraTextLabel extraLabel;

    bool styleDiffersFromRoute;
    RouteConnection* fromConnection;
    std::unique_ptr<RouteConnection> toConnection;
    std::unique_ptr<Via::Control::RouteNodeState> &currentState;

    void centerNodeLabelBox();    


public:
    RouteNode(RouteNodeShape *newNode, const QString &nodeLabelText, const QString &extraTextLabelText, std::unique_ptr<Via::Control::RouteNodeState> &state);
    RouteNode(RouteNodeShape *newNode, const QString &nodeLabelText, std::unique_ptr<Via::Control::RouteNodeState> &state);

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;    
    void activateColors() override;

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() override;

    char getShapeKey() const override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void triggerParentMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

    void setNodeOutlineColor(const QColor &color);
    void setOpacity(qreal opacity);
    void setNodeLabelOpacity(qreal opacity);
    void setNodeLabelText(const QString &newText);
    void setShape(RouteNodeShape* newShape);
    void setStyleDiffersFromRoute(bool value);
    void setToConnectionColor(const QColor &color);

    void resetFromConnection();
    void resetToConnection();
    void resetConnections();
    void checkIfStyleIsDifferent(char routeShape, const QColor &routeColor, int routeSize);

    QColor getColors() const;
    RouteConnection* getFromConnection();
    RouteConnection* getToConnection();
    Via::UI::RouteExtraTextLabel* getExtraLabel();
    Via::UI::RouteNodeLabel* getNodeLabel();
    RouteNodeShape* getNodeShape() const;
    bool getStyleDiffersFromRoute() const;

    void connect(RouteNode &from);
    void moveBy(qreal dx, qreal dy);
    QPointF getCenter() const;
    void updateRouteConnections();
};

}
#endif // ROUTENODE_H
