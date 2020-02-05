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

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;
    void activateColors() override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // ROUTEEXTRATEXTLABEL_H
