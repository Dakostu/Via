#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include "../interfaces/shapeable.h"
#include "../data-structures/indexlist.h"
#include "data.h"
#include "routenodedata.h"
#include <list>
#include <QStringList>


namespace Via::Model {

using RouteDataIterator = Via::Structures::IndexList<Via::Model::RouteNodeData>::iterator;

struct RouteData : public Data, public Via::Interfaces::Shapeable
{
    static constexpr bool DEFAULT_SHOW_ORDER = true;

    static inline const char* ROUTE_NAME_KEY = "n";
    static inline const char* ROUTE_SIZE_KEY = "s";
    static inline const char* ROUTE_COLOR_KEY = "c";
    static inline const char* ROUTE_SHOW_ORDER_KEY = "o";
    static inline const char* ROUTE_SHAPE_KEY = "p";
    static inline const char* ROUTE_NODES_KEY = "a";

    bool showOrder;
    char style;
    Via::Structures::IndexList<RouteNodeData> nodes;

    RouteNodeData generateNewNode(int x, int y);
    void refreshNames(RouteDataIterator&& it, size_t index);

public:
    RouteData();
    RouteData(const QColor &color, char newStyle);
    RouteData(const QJsonObject &object);

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() const override;

    void setColors(const QColor &routeColor) override;
    void activateColors() override;
    void setElementSize(int newSize) override;

    char getShapeKey() const override;
    void setShapeKey(char newStyle) override;

    bool getShowOrder() const;
    RouteNodeData& getFirstNode();
    RouteNodeData& getLastNode();
    QStringList getNodeTitles();
    Via::Structures::IndexList<RouteNodeData> getNodes() const;

    void setShowOrder(bool value);

    void addNode(const RouteNodeData &node);
    void eraseNode(size_t index);

    size_t length() const;
    RouteNodeData& operator[](size_t index);

    bool operator==(const RouteData &other) const;
};

}

#endif // ROUTEDATA_H
