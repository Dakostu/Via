#ifndef ROUTENODEDATA_H
#define ROUTENODEDATA_H

#include "../interfaces/serializable.h"
#include <QString>
#include <QColor>

class RouteNodeData : public Serializable
{
    QString nodeName;
    QString nodeLabel;
    int x;
    int y;
    bool differentStyleFromRoute;
    bool invisible;
    QColor color;
    int size;

public:
    RouteNodeData();
    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() override;
};

#endif // ROUTENODEDATA_H
