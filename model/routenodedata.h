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
    RouteNodeData(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    bool isStyleDifferentFromRoute();
    void setColor(QColor &newColor);
};

#endif // ROUTENODEDATA_H
