#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../interfaces/serializable.h"
#include "routenodedata.h"
#include <QLinkedList>

class RouteData : public Serializable
{
    QString name;
    int size;
    QColor color;
    bool showDirection;
    std::list<RouteNodeData> nodes;

public:
    RouteData();
    RouteData(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;
};

#endif // ROUTEDATA_H
