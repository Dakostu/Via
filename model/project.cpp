#include "project.h"
#include <QBuffer>
#include <QByteArray>
#include <QJsonArray>


Project::Project(const QString &newFileName, const QPixmap &map)
    : fileName(newFileName), imagePixMap(map), hasbeenModified(false)
{

}

Project::Project(const QJsonObject &object) : hasbeenModified(false)
{
    fromJSON(object);
}

void Project::fromJSON(const QJsonObject &object) {

    pixMapFromBytes(object["image"]);
    fileName = object["fileName"].toString();

    auto routesJSON = object["routes"].toArray();

    for (const auto routeJSON : routesJSON) {
        RouteData currentRoute(routeJSON.toObject());
        routes.emplace(currentRoute.getName(), currentRoute);
    }
}

bool Project::getHasbeenModified() const
{
    return hasbeenModified;
}

void Project::setHasbeenModified(bool value)
{
    hasbeenModified = value;
}

QString Project::getFileName() const
{
    return fileName;
}

std::unordered_map<QString, RouteData> Project::getRoutes() const
{
    return routes;
}

QByteArray Project::pixMapToBytes() const {
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    imagePixMap.save(&buffer, "PNG");
    auto toBase = buffer.data().toBase64();
    return toBase;
}

void Project::pixMapFromBytes(const QJsonValue &bytes) {
    auto decodedBytes = bytes.toString().toLatin1();
    auto fromBase = QByteArray::fromBase64(decodedBytes);
    imagePixMap.loadFromData(QByteArray::fromBase64(decodedBytes));
}

QJsonObject Project::toJSON() const {
    QJsonObject projectJSON;

    projectJSON["image"] = QString(pixMapToBytes());
    projectJSON["fileName"] = fileName;

    QJsonArray routesJSON;

    for (const auto &route : routes) {
        routesJSON.append(route.second.toJSON());
    }
    projectJSON["routes"] = routesJSON;

    return projectJSON;
}

void Project::addRoute(RouteData &route) {
    route.setName(QString("Route %1").arg(routes.size() + 1));
    routes.emplace(route.getName(), route);
}

bool Project::operator==(const Project &other) const {
    return this->fileName == other.fileName
            && this->pixMapToBytes() == other.pixMapToBytes()
            && this->routes == other.routes;
}
