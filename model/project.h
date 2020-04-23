#ifndef PROJECT_H
#define PROJECT_H

#include "../data-structures/indexlist.h"
#include "../interfaces/serializable.h"
#include "../shapes/route.h"
#include <QJsonArray>
#include <QLatin1String>
#include <QPixmap>
#include <QString>
#include <vector>

namespace Via::Model {

class Project : public Via::Interfaces::Serializable
{    
    QString fileName;
    QPixmap imagePixMap;
    QJsonArray routesJSON;
    bool hasbeenModified;
    int totalCreatedRoutes;    
    Via::Structures::IndexList<std::unique_ptr<Via::Shapes::Route>> routes;

    static inline const char* PROJECT_IMAGE_KEY = "i";
    static inline const char* PROJECT_FILENAME_KEY = "n";
    static inline const char* PROJECT_TOTAL_CREATED_ROUTES_KEY = "t";
    static inline const char* PROJECT_ROUTES_KEY = "r";

    QByteArray pixMapToBytes() const;
    void pixMapFromBytes(const QJsonValue &bytes);

public:
    Project(const QString &newFileName, const QPixmap &map);
    Project(const QJsonObject &object);

    void fromJSON(const QJsonObject &object) override;
    QJsonObject toJSON() override;

    bool getHasbeenModified() const;
    QPixmap getImagePixMap() const;
    QJsonArray getRoutesJSON() const;
    QString getFileName() const;
    std::vector<Via::Shapes::Route*> getRoutes();

    void setHasbeenModified(bool value);

    void addRoute(Via::Shapes::Route &route);
    void deleteRoute(size_t index);
    void swapRoutes(size_t i, size_t j);

    void setFileName(const QString &value);

    bool operator==(const Project &other) const;
    Via::Shapes::Route& operator[](size_t index);
};

}

#endif // PROJECT_H
