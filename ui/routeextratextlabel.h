#ifndef ROUTEEXTRATEXTLABEL_H
#define ROUTEEXTRATEXTLABEL_H

#include "../interfaces/viewcustomizable.h"
#include <QGraphicsSimpleTextItem>

class RouteExtraTextLabel : public QGraphicsSimpleTextItem, public ViewCustomizable
{
public:
    RouteExtraTextLabel(QString text);

    virtual void setSize(qreal newSize) override;
    virtual void setColors(const QColor &color) override;
    virtual void setDefaultColors() override;
};

#endif // ROUTEEXTRATEXTLABEL_H
