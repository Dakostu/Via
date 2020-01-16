#ifndef ROUTECONNECTION_H
#define ROUTECONNECTION_H

#include "../interfaces/viewcustomizable.h"
#include "../interfaces/nodeshapeable.h"
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>

class RouteConnection : public QGraphicsLineItem, public ViewCustomizable
{
    QPen defaultPen;
    QPen currentPen;
    std::unique_ptr<QLineF> cartesianLine;

    //std::unique_ptr<NodeShapeable> midShape;

public:
    RouteConnection(QPointF from, QPointF to, QColor color);

    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void setSize(qreal newSize) override;
    virtual QPen getPen();
    virtual void setNewPosition(QPointF p1, QPointF p2);
    QPointF p1();
    QPointF p2();

};

#endif // ROUTECONNECTION_H
