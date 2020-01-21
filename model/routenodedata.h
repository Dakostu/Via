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
    bool invisible;
    QColor color;
    int size;

public:
    RouteNodeData();
    RouteNodeData(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    bool isStyleDifferentFromRoute();
    QString getNodeName() const;
    QString getNodeLabel() const;
    int getX() const;
    int getSize() const;
    bool getInvisible() const;
    QColor getColor() const;

    void setColor(QColor &newColor);
    void setNodeName(const QString &value);
    void setNodeLabel(const QString &value);
    void setX(int value);
    void setInvisible(bool value);
    void setSize(int value);
};

#endif // ROUTENODEDATA_H
