#ifndef ROUTEEXTRATEXTLABEL_H
#define ROUTEEXTRATEXTLABEL_H

#include "../interfaces/viewcustomizable.h"
#include "../interfaces/nodeshapeable.h"
#include <QGraphicsSimpleTextItem>
#include <QMouseEvent>

namespace Via::UI {

class RouteExtraTextLabel : public QGraphicsSimpleTextItem, public Via::Interfaces::ViewCustomizable
{

protected:
    Via::Interfaces::NodeShapeable *parentNode;

public:
    RouteExtraTextLabel(QString text, Via::Interfaces::NodeShapeable *parent);

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;
    void activateColors() override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* hoverEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

}

#endif // ROUTEEXTRATEXTLABEL_H
