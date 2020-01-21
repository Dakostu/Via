#ifndef ROUTENODEDATA_H
#define ROUTENODEDATA_H

#include "../interfaces/serializable.h"
#include <QString>
#include <QColor>

class RouteNodeData : public Serializable
{
    QString nodeName;
    QString nodeLabel;
    int x;
    int y;
    bool differentStyleFromRoute;
    bool nameChanged;
    bool invisible;
    QColor color;
    int nodeSize;

public:
    RouteNodeData();
    RouteNodeData(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    bool isStyleDifferentFromRoute() const;
    QString getNodeName() const;
    QString getNodeLabel() const;
    int getX() const;
    int getY() const;
    int getSize() const;
    bool getInvisible() const;
    QColor getColor() const;
    bool isNameChangedByUser() const;

    void setColor(QColor newColor);
    void setNodeName(const QString &value);
    void setNodeLabel(const QString &value);
    void setX(int value);
    void setY(int value);
    void setPos(int newX, int newY);
    void setInvisible(bool value);
    void setSize(int value);
    void setDifferentStyleFromRoute(bool value);
    void setNameChangedByUser(bool value);

    bool operator==(const RouteNodeData &other) const;
};

#endif // ROUTENODEDATA_H
