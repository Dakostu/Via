#ifndef ROUTE_H
#define ROUTE_H

#include "../data-structures/indexlist.h"
#include "../controller/states/routenodestate.h"
#include "../interfaces/mapviewplaceable.h"
#include "../interfaces/serializable.h"
#include "../interfaces/shapekeymodifiable.h"
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


class Route : public Via::Interfaces::MapViewPlaceable,
        public Via::Interfaces::ShapeKeyModifiable,
        public Via::Interfaces::Serializable
{
protected:
    static constexpr qreal TEMPORARY_NODE_OPACITY = 0.5;

    bool showOrder;
    QColor routeColor;
    RouteNodeShapeFactory nodeShapeFactory;
    QGraphicsScene *currentScene;
    std::unique_ptr<Via::Control::RouteNodeState> &currentState;

    Via::Structures::IndexList<RouteNode*> nodes;

    void connectNodes(Via::Shapes::RouteNode &from, Via::Shapes::RouteNode &to);
    void swapConnections(size_t firstNodeIndex, size_t secondNodeIndex);
    void swapNodeNamesConsideringUserChanges(Via::Shapes::RouteNode &fromNode, Via::Shapes::RouteNode &withNode, size_t index);
    void refreshNodeLabels(size_t index = 0);

    Via::Shapes::RouteNode* getLastVisibleRouteNode();
    Via::Shapes::RouteNode* getPreviousVisibleRouteNode(size_t index);
    Via::Shapes::RouteNode* getNextVisibleRouteNode(size_t index);
    size_t getIndexOfPreviousVisibileRouteNode(size_t currentRouteNodeIndex);
    size_t getIndexOfNextVisibileRouteNode(size_t currentRouteNodeIndex);

public:
    Route(const QColor &color, const QString &selectedStyle, QGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state);
    Route(const QColor &color, char selectedStyle, QGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state);
    Route(const QJsonObject &object, QGraphicsScene *scene, std::unique_ptr<Via::Control::RouteNodeState> &state);

    ~Route();

    QColor getColors() override;

    void setColors(const QColor &color) override;
    void activateColors() override;

    Via::Structures::IndexList<RouteNode*>& getNodes();
    void setShapeKey(char newStyle) override;

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() override;

    void setVisible(bool isVisible) override;

    void addNode(qreal x, qreal y);
    void addTemporaryPreviewNode(qreal x, qreal y);
    void removeTemporaryPreviewNode();
    bool hasTemporaryPreviewNode();
    void eraseNode(size_t index);
    void eraseAllNodes();
    void swapNodes(size_t firstNodeIndex, size_t secondNodeIndex);    

    bool getShowOrder() const;
    QString getRouteStyleAsUIString();
    QString getRouteNodeStyleAsUIString(size_t nodeIndex);

    void setElementSize(int newSize) override;
    void setShowOrder(bool value);
    void setColorsOfNode(size_t routeNodeIndex, const QColor &newColor);
    void setCurrentScene(QGraphicsScene *value);
    void setCurrentState(std::unique_ptr<Via::Control::RouteNodeState> &value);
    void setShapeKey(const QString &newStyle);
    void setStyleOfNode(size_t routeNodeIndex, char newStyle);
    void setStyleOfNode(size_t routeNodeIndex, const QString &newStyle);
    void setVisibilityOfNode(size_t routeNodeIndex, bool isCurrentlyVisible);
    size_t size();

    RouteNode& operator[](size_t nodeIndex);
};

}
#endif // ROUTE_H
