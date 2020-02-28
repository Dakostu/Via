#ifndef ROUTENODEDATA_H
#define ROUTENODEDATA_H

#include "data.h"
#include <QString>
#include <QColor>

namespace Via::Model {

class RouteNodeData : public Data
{
    QString nodeLabel;
    int x;
    int y;
    bool differentStyleFromRoute;
    bool nameChanged;
    bool invisible;
    char style;

    static const char* NODE_NAME_KEY;
    static const char* NODE_LABEL_KEY;
    static const char* NODE_X_KEY;
    static const char* NODE_Y_KEY;
    static const char* NODE_DIFFERENT_STYLE_KEY;
    static const char* NODE_NAME_CHANGED_KEY;
    static const char* NODE_INVISIBLE_KEY;
    static const char* NODE_COLOR_KEY;
    static const char* NODE_SIZE_KEY;
    static const char* NODE_SHAPE_KEY;

public:
    RouteNodeData();
    RouteNodeData(const QColor &color);
    RouteNodeData(const QJsonObject &object);

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() const override;

    void setColors(const QColor &currentColor) override;
    void activateColors() override;

    bool isStyleDifferentFromRoute() const;
    QString getNodeLabel() const;
    int getX() const;
    int getY() const;
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
    char getStyle() const;
    void setStyle(char value);
};

}

#endif // ROUTENODEDATA_H
