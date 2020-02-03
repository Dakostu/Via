#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../data-structures/indexlist.h"
#include "data.h"
#include "routenodedata.h"
#include <list>
#include <QStringList>

using RouteDataIterator = IndexList<RouteNodeData>::iterator;

class RouteData : public Data
{
    static constexpr bool DEFAULT_SHOW_ORDER = true;

    bool showOrder;
    IndexList<RouteNodeData> nodes;

    RouteNodeData generateNewNode(int x, int y);
    void refreshNames(RouteDataIterator& it, size_t index);

public:
    RouteData();
    RouteData(const QColor &color);
    RouteData(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    virtual void setColors(const QColor &routeColor) override;
    virtual void setDefaultColors() override;
    virtual void setElementSize(int newSize) override;

    bool getShowOrder() const;
    RouteNodeData& getFirstNode();
    RouteNodeData& getLastNode();
    QStringList getNodeTitles();
    IndexList<RouteNodeData> getNodes() const;

    void setShowOrder(bool value);

    void addNode(int x, int y);
    void addNode(int x, int y, size_t index);
    void addNode(const RouteNodeData &node);
    void eraseNode(size_t index);

    size_t length() const;
    RouteNodeData& operator[](int index);

    bool operator==(const RouteData &other) const;
};

#endif // ROUTEDATA_H
