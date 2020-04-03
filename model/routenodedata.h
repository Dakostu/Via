#ifndef ROUTENODEDATA_H
#define ROUTENODEDATA_H

#include "../interfaces/shapeable.h"
#include "data.h"
#include <QString>
#include <QColor>

namespace Via::Model {

struct RouteNodeData : public Data, public Via::Interfaces::Shapeable
{
    QString nodeLabel;
    int x;
    int y;
    bool differentStyleFromRoute;
    bool nameChanged;
    bool invisible;
    char style;

    static inline const char* NODE_NAME_KEY = "n";
    static inline const char* NODE_LABEL_KEY = "l";
    static inline const char* NODE_X_KEY = "x";
    static inline const char* NODE_Y_KEY = "y";
    static inline const char* NODE_DIFFERENT_STYLE_KEY = "f";
    static inline const char* NODE_NAME_CHANGED_KEY = "c";
    static inline const char* NODE_INVISIBLE_KEY = "i";
    static inline const char* NODE_COLOR_KEY = "c";
    static inline const char* NODE_SIZE_KEY = "s";
    static inline const char* NODE_SHAPE_KEY = "p";

public:
    RouteNodeData();
    RouteNodeData(const QColor &color);
    RouteNodeData(const QJsonObject &object);

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() const override;

    void setColors(const QColor &currentColor) override;
    void activateColors() override;

    char getShapeKey() const override;
    void setShapeKey(char value) override;

    bool isStyleDifferentFromRoute() const;
    QString getNodeLabel() const;
    int getX() const;
    int getY() const;
    QPointF getCenter() const;
    bool getInvisible() const;
    bool isNameChangedByUser() const;

    void setNodeLabel(const QString &value);
    void setX(int value);
    void setY(int value);
    void setPos(int newX, int newY);
    void setInvisible(bool value);
    void setDifferentStyleFromRoute(bool value);
    void setNameChangedByUser(bool value);

    bool operator==(const RouteNodeData &other) const;
};

}

#endif // ROUTENODEDATA_H
