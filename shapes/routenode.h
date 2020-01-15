#ifndef ROUTENODE_H
#define ROUTENODE_H

#include "../interfaces/nodeshapeable.h"
#include "../interfaces/viewcustomizable.h"
#include "../ui/routenodelabel.h"
#include "../ui/routeextratextlabel.h"
#include <QObject>
#include <QGraphicsItemGroup>
#include <memory>

class RouteNode : public QGraphicsItemGroup, public ViewCustomizable
{

    std::unique_ptr<NodeShapeable> node;
    RouteNodeLabel nodeLabel;
    RouteExtraTextLabel extraTextLabel;

    void centerNodeLabelBox();


public:
    RouteNode(NodeShapeable *newNode, QString nodeLabelText, QString extraTextLabelText);
    RouteNode(NodeShapeable *newNode, QString nodeLabelText);

    virtual void setSize(qreal newSize) override;
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;

    RouteExtraTextLabel* getExtraText();

};

#endif // ROUTENODE_H
