#include "project.h"
#include "../ui/localizeduistrings.h"
#include <QBuffer>
#include <QByteArray>
#include <QJsonArray>


Project::Project(const QString &newFileName, const QPixmap &map)
    : fileName(newFileName), imagePixMap(map), hasbeenModified(false), totalCreatedRoutes(0)
{

}

Project::Project(const QJsonObject &object) : hasbeenModified(false)
{
    fromJSON(object);
}

void Project::fromJSON(const QJsonObject &object) {

    pixMapFromBytes(object["image"]);
    fileName = object["fileName"].toString();
    totalCreatedRoutes = object["totalCreatedRoutes"].toInt();

    auto routesJSON = object["routes"].toArray();

    for (const auto routeJSON : routesJSON) {
        RouteData currentRoute(routeJSON.toObject());
        routes.emplace_back(currentRoute);
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

IndexList<RouteData>& Project::getRoutes()
{
    return routes;
}

void Project::setFileName(const QString &value)
{
    fileName = value;
}

QPixmap Project::getImagePixMap() const
{
    return imagePixMap;
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
    projectJSON["totalCreatedRoutes"] = totalCreatedRoutes;

    QJsonArray routesJSON;

    for (const auto &route : routes) {
        routesJSON.append(route.toJSON());
    }
    projectJSON["routes"] = routesJSON;

    return projectJSON;
}

void Project::addRoute(RouteData &route) {
    ++totalCreatedRoutes;
    route.setName(LocalizedUIStrings::getUIString("ROUTE_DEFAULT_NAME").arg(totalCreatedRoutes));
    routes.emplace_back(route);
}

void Project::addRouteNode(RouteNodeData &node, int routeIndex) {
    auto &selectedRoute = *routes[routeIndex];
    node.setName(LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(selectedRoute.length() + 1));
    selectedRoute.addNode(node);
}

void Project::deleteRoute(int index) {
    routes.erase(routes[index]);
}

void Project::swapRoutes(int i, int j) {
    std::swap(*routes[i], *routes[j]);
}

void Project::swapNodes(int routeIndex, int i, int j) {
    auto &firstNode = (*routes[routeIndex])[i];
    auto &secondNode = (*routes[routeIndex])[j];

    std::swap(firstNode, secondNode);

    auto tempName = firstNode.getName();
    firstNode.setName(secondNode.getName());
    secondNode.setName(tempName);
}

bool Project::operator==(const Project &other) const {
    return this->fileName == other.fileName
            && this->pixMapToBytes() == other.pixMapToBytes()
            && this->totalCreatedRoutes == other.totalCreatedRoutes
            && this->routes == other.routes;
}

RouteData& Project::operator[](int index) {
    return *routes[index];
}
