#ifndef ROUTECONNECTION_H
#define ROUTECONNECTION_H

#include "../interfaces/viewcustomizable.h"
#include "routenodeshape.h"
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>

namespace Via::Shapes {

class RouteConnection : public QGraphicsLineItem, public Via::Interfaces::ViewCustomizable
{
    QColor elementColor;
    static constexpr qreal SIZE_FACTOR = 0.2;
    static constexpr qreal SIZE_OFFSET = 3;
    std::unique_ptr<QLineF> cartesianLine;

public:
    RouteConnection(QPointF from, QPointF to, const QColor &color);

    void setColors(const QColor &color) override;
    void activateColors() override;

    void setElementSize(int newSize) override;
    virtual void setNewPosition(QPointF p1, QPointF p2);
    QPointF p1();
    QPointF p2();

};

}

#endif // ROUTECONNECTION_H
