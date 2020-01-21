#ifndef PROJECT_H
#define PROJECT_H

#include "../interfaces/serializable.h"
#include "routedata.h"
#include <QPixmap>
#include <QLatin1String>
#include <QString>
#include <QVector>

class Project : public Serializable
{    
    QString fileName;
    QPixmap imagePixMap;
    bool hasbeenModified;
    QVector<RouteData> routes;

    QLatin1String pixMapToBytes() const;
    void pixMapFromBytes(const QJsonValue &bytes);


public:
    Project(const QString &newFileName, const QPixmap &map);
    Project(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    bool getHasbeenModified() const;
    void setHasbeenModified(bool value);

    void addRoute(const RouteData &route);

    const RouteData& operator[](int index);
    bool operator==(const Project &other) const;
};

#endif // PROJECT_H
