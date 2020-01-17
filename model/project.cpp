#include "project.h"
#include <QBuffer>
#include <QByteArray>
#include <QJsonArray>

Project::Project()
{

}

void Project::fromJSON(const QJsonObject &object) {

    pixMapFromBytes(object["image"]);
    fileName = object["fileName"].toString();

    auto routesJSON = object["routes"].toArray();

    for (const auto &routeJSON : routesJSON) {
        RouteData currentRoute;
        currentRoute.fromJSON(routeJSON.toObject());
        routes.append(currentRoute);
    }
}

QLatin1String Project::pixMapToBytes() const {
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    imagePixMap.save(&buffer);
    return QLatin1String(buffer.data().toBase64());
}

void Project::pixMapFromBytes(const QJsonValue &bytes) {
    auto decodedBytes = bytes.toString().toLatin1();
    imagePixMap.loadFromData(QByteArray::fromBase64(decodedBytes));
}

QJsonObject Project::toJSON() const {
    QJsonObject projectJSON;

    projectJSON["image"] = pixMapToBytes();
    projectJSON["fileName"] = fileName;

    QJsonArray routesJSON;

    for (const auto &route : routes) {
        routesJSON.append(route.toJSON());
    }
    projectJSON["routes"] = routesJSON;

    return projectJSON;
}

