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
    void refreshNames(RouteDataIterator& it, int index);

public:
    RouteData();
    RouteData(const QColor &color);
    RouteData(const QJsonObject &object);

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() const override;

    void setColors(const QColor &routeColor) override;
    void activateColors() override;
    void setElementSize(int newSize) override;

    bool getShowOrder() const;
    RouteNodeData& getFirstNode();
    RouteNodeData& getLastNode();
    QStringList getNodeTitles();
    IndexList<RouteNodeData> getNodes() const;

    void setShowOrder(bool value);

    void addNode(int x, int y);
    void addNode(int x, int y, int index);
    void addNode(const RouteNodeData &node);
    void eraseNode(int index);

    size_t length() const;
    RouteNodeData& operator[](int index);

    bool operator==(const RouteData &other) const;
};

#endif // ROUTEDATA_H
