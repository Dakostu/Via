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

    QString getName() const;
    int getSize() const;
    QColor getColor() const;
    bool getShowDirection() const;

    void setName(const QString &value);
    void setSize(int value);
    void setColor(const QColor &value);
    void setShowDirection(bool value);

    void addNode(const RouteNodeData node&);

    RouteNodeData& operator[](size_t index)M;
};

#endif // ROUTEDATA_H
