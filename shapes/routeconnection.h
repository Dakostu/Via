#ifndef ROUTECONNECTION_H
#define ROUTECONNECTION_H

#include "../interfaces/viewcustomizable.h"
#include "../interfaces/nodeshapeable.h"
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>

class RouteConnection : public QGraphicsLineItem, public ViewCustomizable
{
    const QPen defaultPen;
    static constexpr qreal SIZE_FACTOR = 0.2;
    static constexpr qreal SIZE_OFFSET = 3;
    std::unique_ptr<QLineF> cartesianLine;

public:
    RouteConnection(QPointF from, QPointF to, QColor color);

    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;

    virtual void setSize(qreal newSize) override;
    virtual void setNewPosition(QPointF p1, QPointF p2);
    QPointF p1();
    QPointF p2();

};

#endif // ROUTECONNECTION_H
