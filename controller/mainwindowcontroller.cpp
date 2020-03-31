#include "../controller/states/mainwindowmovenodestate.h"
#include "../controller/states/mapviewmovenodestate.h"
#include "../controller/states/routenodemovenodestate.h"
#include "mainwindowcontroller.h"
#include "programversion.h"
#include "jsonfile.h"
#include "../ui/localizeduistrings.h"

using namespace Via::Control;
using namespace Via::Model;

MainWindowController::MainWindowController()
    : currentProject{},
      currentMainWindowState(new MainWindowMoveNodeState),
      currentMapViewState(new MapViewMoveNodeState),
      currentRouteNodeState(new RouteNodeMoveNodeState)
{

}

void MainWindowController::addProject(const Project &project) {
    openProjects.emplace(project.getFileName(), project);
    setCurrentProject(project.getFileName());
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

    if (openProjects.find(fileName) == openProjects.end()) {
        JSONFile readFile(fileName);
        auto loadedProjects = readFile.load();
        auto project = Project(loadedProjects[0].toObject());
        openProjects.insert_or_assign(fileName, project);
    }

    setCurrentProject(fileName);
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

Project* MainWindowController::getCurrentProject() {
    return currentProject;
}

void MainWindowController::setCurrentProject(const QString &fileName) {
    currentProject = &openProjects.at(fileName);
    emit currentProjectChanged();
}

QStringListModel& MainWindowController::getCurrentRouteTitles() {
    QStringList currentRouteList;

    for (const auto &route : currentProject->getRoutes()) {
        currentRouteList << route.getName();
    }

    currentRouteTitles.setStringList(currentRouteList);
    return currentRouteTitles;
}

QStringListModel& MainWindowController::getNodeTitlesOfRoute(size_t index) {
    routeNodeTitles.setStringList(getCurrentProject()->getRoutes()[index]->getNodeTitles());
    return routeNodeTitles;
}

void MainWindowController::deleteRouteofCurrentProject(size_t index) {
    currentProject->deleteRoute(index);
    emit routeListChanged();
}

void MainWindowController::deleteNodeofRoute(size_t routeIndex, size_t nodeIndex) {
    currentProject->getRoutes()[routeIndex]->eraseNode(nodeIndex);
    emit routeNodeListChanged();
}

void MainWindowController::swapCurrentProjectRoutes(size_t firstRoute, size_t secondRoute) {
    currentProject->swapRoutes(firstRoute, secondRoute);
    emit routeListChanged();
}

void MainWindowController::swapNodesOfRoute(size_t routeIndex, size_t firstNode, size_t secondNode)  {
    currentProject->swapNodes(routeIndex, firstNode, secondNode);
    emit routeNodeListChanged();
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


void MainWindowController::setStyleOfCurrentRoute(size_t routeIndex, char newStyle) {
    auto &currentNodeData = (*currentProject->getRoutes()[routeIndex]);
    currentNodeData.setShapeKey(newStyle);
}

void MainWindowController::setStyleOfCurrentRouteNode(size_t routeIndex, size_t nodeIndex, char newStyle, bool isDifferentNow) {
    auto &currentNodeData = (*currentProject->getRoutes()[routeIndex])[nodeIndex];
    currentNodeData.setShapeKey(newStyle);
    currentNodeData.setDifferentStyleFromRoute(isDifferentNow);
}

void MainWindowController::setColorOfCurrentRoute(size_t routeIndex, const QColor &newColor) {
    auto &currentNodeData = (*currentProject->getRoutes()[routeIndex]);
    currentNodeData.setColors(newColor);
}

void MainWindowController::setColorOfCurrentRouteNode(size_t routeIndex, size_t nodeIndex, const QColor &newColor, bool isDifferentNow) {
    auto &currentNodeData = (*currentProject->getRoutes()[routeIndex])[nodeIndex];
    currentNodeData.setColors(newColor);
    currentNodeData.setDifferentStyleFromRoute(isDifferentNow);
}

void MainWindowController::addNewRouteToCurrentProject(const QColor &newColor, char newStyle) {
    RouteData newRoute(newColor, newStyle);
    currentProject->addRoute(newRoute);
    emit routeListChanged();
}

void MainWindowController::addNewNodeToRoute(int x, int y, const QColor &newColor, size_t routeIndex) {
    RouteNodeData newRouteNode(newColor);
    newRouteNode.setX(x);
    newRouteNode.setY(y);
    currentProject->addRouteNode(newRouteNode, routeIndex);
    emit routeNodeListChanged();
}

size_t MainWindowController::amountOfOpenProjects() {
    return openProjects.size();
}
