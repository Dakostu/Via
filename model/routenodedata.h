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
};

}

#endif // ROUTENODEDATA_H
