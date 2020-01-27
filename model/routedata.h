#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../data-structures/indexlist.h"
#include "../interfaces/serializable.h"
#include "../interfaces/viewcustomizable.h"
#include "routenodedata.h"
#include <list>
#include <variant>


using RouteDataIterator = IndexList<RouteNodeData>::iterator;

class RouteData : public Serializable, public ViewCustomizable
{
    static constexpr bool DEFAULT_SHOW_DIR = false;

    QString name;
    QColor routeColor;
    bool showDirection;
    IndexList<RouteNodeData> nodes;

    RouteNodeData generateNewNode(int x, int y);
    void refreshNames(RouteDataIterator& it, size_t index);

public:
    RouteData();
    RouteData(const QColor &routeColor);
    RouteData(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    virtual void setColors(const QColor &routeColor) override;
    virtual void setDefaultColors() override;
    virtual void setElementSize(int newSize) override;

    QString getName() const;
    QColor getColor() const;
    bool getShowDirection() const;
    RouteNodeData& getFirstNode();
    RouteNodeData& getLastNode();

    void setName(const QString &value);
    void setShowDirection(bool value);

    void addNode(int x, int y);
    void addNode(int x, int y, size_t index);
    void addNode(const RouteNodeData &node);
    void eraseNode(size_t index);

    size_t length() const;
    RouteNodeData& operator[](size_t index);

    bool operator==(const RouteData &other) const;
};

#endif // ROUTEDATA_H
