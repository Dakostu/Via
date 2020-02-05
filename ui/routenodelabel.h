#ifndef ROUTENODELABEL_H
#define ROUTENODELABEL_H

#include "../interfaces/viewcustomizable.h"
#include <QGraphicsSimpleTextItem>

class RouteNodeLabel : public QGraphicsSimpleTextItem, public ViewCustomizable
{
public:
    RouteNodeLabel(QString text);

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;
    void activateColors() override;


};

#endif // ROUTENODELABEL_H
