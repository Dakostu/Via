#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../data-structures/indexlist.h"
#include "data.h"
#include "routenodedata.h"
#include <list>
#include <QStringList>


namespace Via::Model {

using RouteDataIterator = Via::Structures::IndexList<Via::Model::RouteNodeData>::iterator;

class RouteData : public Data
{
    static constexpr bool DEFAULT_SHOW_ORDER = true;

    static const char* ROUTE_NAME_KEY;
    static const char* ROUTE_SIZE_KEY;
    static const char* ROUTE_COLOR_KEY;
    static const char* ROUTE_SHOW_ORDER_KEY;
    static const char* ROUTE_SHAPE_KEY;
    static const char* ROUTE_NODES_KEY;

    bool showOrder;
    Via::Structures::IndexList<RouteNodeData> nodes;

    RouteNodeData generateNewNode(int x, int y);
    void refreshNames(RouteDataIterator&& it, int index);

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
    Via::Structures::IndexList<RouteNodeData> getNodes() const;

    void setShowOrder(bool value);

    void addNode(const RouteNodeData &node);
    void eraseNode(int index);

    size_t length() const;
    RouteNodeData& operator[](int index);

    bool operator==(const RouteData &other) const;
};

}

#endif // ROUTEDATA_H
