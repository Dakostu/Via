#ifndef ROUTEEXTRATEXTLABEL_H
#define ROUTEEXTRATEXTLABEL_H

#include "../interfaces/viewcustomizable.h"
#include "../interfaces/nodeshapeable.h"
#include <QGraphicsSimpleTextItem>
#include <QMouseEvent>

class RouteExtraTextLabel : public QGraphicsSimpleTextItem, public ViewCustomizable
{

protected:
    NodeShapeable *parentNode;

public:
    RouteExtraTextLabel(QString text, NodeShapeable *parent);

    virtual void setElementSize(int newSize) override;
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // ROUTEEXTRATEXTLABEL_H
