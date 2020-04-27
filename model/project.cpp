#include "../l10n/localizeduistrings.h"
#include "project.h"
#include <QBuffer>
#include <QByteArray>
#include <QJsonArray>

using namespace Via::L10n;
using namespace Via::Model;
using namespace Via::Shapes;
using namespace Via::Structures;
using namespace Via::UI;

Project::Project(const QString &newFileName, const QPixmap &map)
    : fileName(newFileName), imagePixMap(map), hasbeenModified(false), totalCreatedRoutes(0)
{

}

Project::Project(const QJsonObject &object) : hasbeenModified(false), totalCreatedRoutes(0)
{
    fromJSON(object);
}

void Project::fromJSON(const QJsonObject &object) {
    pixMapFromBytes(object[PROJECT_IMAGE_KEY]);
    fileName = object[PROJECT_FILENAME_KEY].toString();

    routesJSON = object[PROJECT_ROUTES_KEY].toArray();
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

std::vector<Route*> Project::getRoutes()
{
    std::vector<Route*> routePointers(routes.size());
    auto currentRoute = routes.begin();

    for (size_t i = 0; i < routes.size(); ++i) {
        routePointers[i] = (currentRoute++)->get();
    }

    return routePointers;
}

void Project::setFileName(const QString &value)
{
    fileName = value;
}

QPixmap Project::getImagePixMap() const
{
    return imagePixMap;
}

QJsonArray Project::getRoutesJSON() const
{
    return routesJSON;
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
    imagePixMap.loadFromData(QByteArray::fromBase64(decodedBytes));
}

QJsonObject Project::toJSON() {
    QJsonObject projectJSON;

    projectJSON[PROJECT_IMAGE_KEY] = QString(pixMapToBytes());
    projectJSON[PROJECT_FILENAME_KEY] = fileName;
    projectJSON[PROJECT_TOTAL_CREATED_ROUTES_KEY] = totalCreatedRoutes;

    routesJSON = QJsonArray();

    for (const auto &route : routes) {
        routesJSON.append(route->toJSON());
    }
    projectJSON[PROJECT_ROUTES_KEY] = routesJSON;

    return projectJSON;
}

void Project::addRoute(Route &route) {
    ++totalCreatedRoutes;
    if (!route.isNameChangedByUser()) {
        route.setName(LocalizedUIStrings::getUIString("ROUTE_DEFAULT_NAME").arg(totalCreatedRoutes));
    }
    routes.emplace_back(&route);
}

void Project::deleteRoute(size_t index) {
    routes.erase(routes[index]);
}

void Project::swapRoutes(size_t i, size_t j) {
    auto &firstRoute = *routes[i];
    auto &secondRoute = *routes[j];

    firstRoute.swap(secondRoute);

    // swap names, after swapping objects

    auto index = std::max(i,j);
    auto routeDefaultNamePlusOne = QString(LocalizedUIStrings::getUIString("ROUTE_DEFAULT_NAME").arg(index + 1));
    auto routeDefaultName = QString(LocalizedUIStrings::getUIString("ROUTE_DEFAULT_NAME").arg(index));

    if (i < j) {
        firstRoute->swapNamesConsideringDefaultNamesWith(secondRoute.get(), routeDefaultName, routeDefaultNamePlusOne);
    } else {
        secondRoute->swapNamesConsideringDefaultNamesWith(firstRoute.get(), routeDefaultName, routeDefaultNamePlusOne);
    }

}

bool Project::operator==(const Project &other) const {
    return this->fileName == other.fileName
            && this->pixMapToBytes() == other.pixMapToBytes()
            && this->totalCreatedRoutes == other.totalCreatedRoutes;
}

Route& Project::operator[](size_t index) {
    return **routes[index];
}
