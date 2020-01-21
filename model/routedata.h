#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../interfaces/serializable.h"
#include "routenodedata.h"
#include <list>
#include <variant>


class RouteData : public Serializable
{
    QString name;
    int size;
    QColor color;
    bool showDirection;
    std::list<RouteNodeData> nodes;

    std::list<RouteNodeData>::iterator iterateToPosition(size_t index);

    RouteNodeData generateNewNode(int x, int y);

public:
    RouteData();
    RouteData(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    QString getName() const;
    int getSize() const;
    QColor getColor() const;
    bool getShowDirection() const;
    RouteNodeData& getFirstNode();
    RouteNodeData& getLastNode();

    void setName(const QString &value);
    void setSize(int value);
    void setColor(const QColor &value);
    void setShowDirection(bool value);

    void addNode(int x, int y);
    void addNode(int x, int y, size_t index);

    RouteNodeData& operator[](size_t index);
};

#endif // ROUTEDATA_H
