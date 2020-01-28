#ifndef PROJECT_H
#define PROJECT_H

#include "../data-structures/indexlist.h"
#include "../interfaces/serializable.h"
#include "routedata.h"
#include <QPixmap>
#include <QLatin1String>
#include <QString>
#include <vector>

class Project : public Serializable
{    
    QString fileName;
    QPixmap imagePixMap;
    bool hasbeenModified;
    IndexList<RouteData> routes;

    QByteArray pixMapToBytes() const;
    void pixMapFromBytes(const QJsonValue &bytes);

public:
    Project(const QString &newFileName, const QPixmap &map);
    Project(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;

    bool getHasbeenModified() const;
    void setHasbeenModified(bool value);
    QString getFileName() const;
    IndexList<RouteData> getRoutes() const;

    void addRoute(RouteData &route);
    void deleteRoute(size_t index);

    bool operator==(const Project &other) const;

};

#endif // PROJECT_H
