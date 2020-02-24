#ifndef PROJECT_H
#define PROJECT_H

#include "../data-structures/indexlist.h"
#include "../interfaces/serializable.h"
#include "routedata.h"
#include <QPixmap>
#include <QLatin1String>
#include <QString>
#include <vector>

namespace Via::Model {

class Project : public Via::Interfaces::Serializable
{    
    QString fileName;
    QPixmap imagePixMap;
    bool hasbeenModified;
    int totalCreatedRoutes;    
    Via::Structures::IndexList<RouteData> routes;

    static const char* PROJECT_IMAGE_KEY;
    static const char* PROJECT_FILENAME_KEY;
    static const char* PROJECT_TOTAL_CREATED_ROUTES_KEY;
    static const char* PROJECT_ROUTES_KEY;

    QByteArray pixMapToBytes() const;
    void pixMapFromBytes(const QJsonValue &bytes);

public:
    Project(const QString &newFileName, const QPixmap &map);
    Project(const QJsonObject &object);

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() const override;

    bool getHasbeenModified() const;
    void setHasbeenModified(bool value);
    QString getFileName() const;
    Via::Structures::IndexList<RouteData>& getRoutes();

    void addRoute(RouteData &route);
    void addRouteNode(RouteNodeData &node, int routeIndex);
    void deleteRoute(int index);
    void swapRoutes(int i, int j);
    void swapNodes(int routeIndex, int i, int j);

    void setFileName(const QString &value);

    bool operator==(const Project &other) const;
    RouteData& operator[](int index);
    QPixmap getImagePixMap() const;
};

}

#endif // PROJECT_H
