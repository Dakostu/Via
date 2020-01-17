#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../interfaces/serializable.h"
#include "routenodedata.h"
class RouteData : public Serializable
{
    QString name;
    int size;
    QColor color;
    bool showDirection;
    QList<RouteNodeData> nodes;

public:
    RouteData();
    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;
};

#endif // ROUTEDATA_H
