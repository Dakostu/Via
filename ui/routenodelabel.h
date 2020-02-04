#ifndef ROUTENODELABEL_H
#define ROUTENODELABEL_H

#include "../interfaces/viewcustomizable.h"
#include <QGraphicsSimpleTextItem>

class RouteNodeLabel : public QGraphicsSimpleTextItem, public ViewCustomizable
{
public:
    RouteNodeLabel(QString text);

    virtual void setElementSize(int newSize) override;
    virtual void setColors(const QColor &color) override;
    virtual void activateColors() override;


};

#endif // ROUTENODELABEL_H
