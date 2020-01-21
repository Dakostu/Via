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
    Project();
    Project(const QJsonObject &object);

    virtual void fromJSON(const QJsonObject &object) override;
    virtual QJsonObject toJSON() const override;
};

#endif // PROJECT_H
