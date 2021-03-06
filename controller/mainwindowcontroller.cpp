#include "../controller/states/mainwindowmovenodestate.h"
#include "../controller/states/mapviewmovenodestate.h"
#include "../controller/states/routenodemovenodestate.h"
#include "mainwindowcontroller.h"
#include "programversion.h"
#include "jsonfile.h"

using namespace Via::Control;
using namespace Via::Model;
using namespace Via::Shapes;
using namespace Via::Interfaces;
using namespace Via::Structures;

MainWindowController::MainWindowController()
    : currentProject{},
      currentMainWindowState(new MainWindowMoveNodeState),
      currentMapViewState(new MapViewMoveNodeState),
      currentRouteNodeState(new RouteNodeMoveNodeState)
{
    connect(&currentRouteList, &CheckableStringListModel::rowCheckChanged, this, [&](auto row, auto visible) {
        emit needToChangeVisibilityOfRoute(row, visible);
    });

    connect(&currentRouteNodeList, &CheckableStringListModel::rowCheckChanged, this, [&](auto row, auto visible) {
        emit needToChangeVisibilityOfCurrentRouteNode(row, visible);
    });
}

void MainWindowController::saveCurrentProjectAs(const QString &fileName) {
    currentProject->setFileName(fileName);

    auto projectJSON = currentProject->toJSON();
    projectJSON[PROGRAM_VER_KEY] = ProgramVersion::generateCurrentProgramVersion()();

    JSONFile saveFile(fileName);
    saveFile += projectJSON;
    saveFile.save();
}

void MainWindowController::saveCurrentProject() {
    saveCurrentProjectAs(currentProject->getFileName());
}

void MainWindowController::loadCurrentProjectFromFile(const QString &fileName) {

    JSONFile readFile(fileName);
    auto loadedProjects = readFile.load();
    auto project = new Project(loadedProjects[0].toObject());

    setCurrentProject(project);
    addFileToRecentlyOpenedProjects(fileName);
}

void MainWindowController::addFileToRecentlyOpenedProjects(const QString &fileName) {

    auto position = std::find(recentlyOpenedProjects.begin(), recentlyOpenedProjects.end(), fileName);

    if (position == recentlyOpenedProjects.end()) {
        recentlyOpenedProjects.emplace_back(fileName);
        if (recentlyOpenedProjects.size() > MAX_LIST_SIZE) {
            recentlyOpenedProjects.pop_front();
        }
    } else {
        auto project = *position;
        recentlyOpenedProjects.erase(position);
        recentlyOpenedProjects.emplace_back(project);
    }

}

void MainWindowController::updateStringListModel(CheckableStringListModel &model,
                                                 const std::vector<MapViewPlaceable*> &mapViewPlaceables) {
    model.removeRows(0, model.rowCount());
    model.insertRows(0, mapViewPlaceables.size());

    for (size_t i = 0; i < mapViewPlaceables.size(); ++i) {
        auto modelIndex = model.index(static_cast<int>(i));
        auto checkState = mapViewPlaceables[i]->isCurrentlyVisible() ? Qt::Checked : Qt::Unchecked;

        model.setDataWithoutSignalEmissions(modelIndex, checkState, Qt::CheckStateRole);
        model.setDataWithoutSignalEmissions(modelIndex, mapViewPlaceables[i]->getName(), Qt::DisplayRole);
        model.setDataWithoutSignalEmissions(modelIndex, mapViewPlaceables[i]->getColors(), Qt::DecorationRole);
    }
}

Project* MainWindowController::getCurrentProject() {
    return currentProject.get();
}

void MainWindowController::setCurrentProject(Project *project) {
    currentProject.reset(project);
    emit currentProjectChanged();
}

QStringListModel& MainWindowController::getCurrentRouteTitles() {
    auto routes = currentProject->getRoutes();
    std::vector<MapViewPlaceable*> mapViewPlaceables(routes.begin(), routes.end());

    updateStringListModel(currentRouteList, mapViewPlaceables);

    return currentRouteList;
}

QStringListModel& MainWindowController::getNodeTitlesOfRoute(size_t index) {
    auto routeNodes = (currentProject->getRoutes()[index])->getNodes();
    std::vector<MapViewPlaceable*> mapViewPlaceables(routeNodes.begin(), routeNodes.end());

    updateStringListModel(currentRouteNodeList, mapViewPlaceables);

    return currentRouteNodeList;
}

std::unique_ptr<MainWindowState>& MainWindowController::getCurrentMainWindowState() {
    return currentMainWindowState;
}

std::unique_ptr<MapViewState>& MainWindowController::getCurrentMapViewState() {
    return currentMapViewState;
}

std::unique_ptr<RouteNodeState>& MainWindowController::getCurrentRouteNodeState() {
    return currentRouteNodeState;
}

Route& MainWindowController::getRouteOfCurrentProject(size_t routeIndex) {
    return (*currentProject)[routeIndex];
}

RouteNode& MainWindowController::getRouteNodeofCurrentProject(size_t routeIndex, size_t routeNodeIndex) {
    return getRouteOfCurrentProject(routeIndex)[routeNodeIndex];
}

void MainWindowController::swapRoutesOfCurrentProject(size_t firstRoute, size_t secondRoute) {
    currentProject->swapRoutes(firstRoute, secondRoute);
}

void MainWindowController::deleteRoute(size_t routeIndex) {
    currentProject->deleteRoute(routeIndex);
}

void MainWindowController::updateRouteNodeColor(size_t routeNodeIndex, const QColor &newColor) {
    auto modelIndex = currentRouteNodeList.index(routeNodeIndex);
    currentRouteNodeList.setData(modelIndex, newColor, Qt::DecorationRole);
}

void MainWindowController::updateRouteColor(size_t routeIndex, const QColor &newColor) {
    auto modelIndex = currentRouteList.index(routeIndex);
    currentRouteList.setData(modelIndex, newColor, Qt::DecorationRole);
}

void MainWindowController::addNewRouteToCurrentProject(Route &newRoute) {
    currentProject->addRoute(newRoute);
}
