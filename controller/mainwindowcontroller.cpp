#include "states/uimovenodesstate.h"
#include "mainwindowcontroller.h"
#include "programversion.h"
#include "jsonfile.h"
#include "../ui/localizeduistrings.h"

using namespace Via::Control;
using namespace Via::Model;

MainWindowController::MainWindowController()
    : currentState(new UIMoveNodesState)
{

}

void MainWindowController::addProject(const Project &project) {
    openProjects.emplace(project.getFileName(), project);
    setCurrentProject(project.getFileName());
}

void MainWindowController::saveCurrentProjectAs(const QString &fileName) {
    currentProject->setFileName(fileName);

    auto projectJSON = currentProject->toJSON();
    projectJSON["programVer"] = ProgramVersion::generateCurrentProgramVersion()();

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

std::unique_ptr<UIState>& MainWindowController::getCurrentState()
{
    return currentState;
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

QStringListModel& MainWindowController::getNodeTitlesOfRoute(int index) {
    routeNodeTitles.setStringList(getCurrentProject()->getRoutes()[index]->getNodeTitles());
    return routeNodeTitles;
}

void MainWindowController::deleteRouteofCurrentProject(int index) {
    currentProject->deleteRoute(index);
    emit routeListChanged();
}

void MainWindowController::deleteNodeofRoute(int routeIndex, int nodeIndex) {
    currentProject->getRoutes()[routeIndex]->eraseNode(nodeIndex);
    emit routeNodeListChanged();
}

void MainWindowController::swapCurrentProjectRoutes(int x, int y) {
    currentProject->swapRoutes(x,y);
    emit routeListChanged();
}

void MainWindowController::swapNodesOfRoute(int routeIndex, int x, int y)  {
    currentProject->swapNodes(routeIndex, x, y);
    emit routeNodeListChanged();
}


void MainWindowController::printCurrentProject() {
    #ifndef QT_NO_PRINTER


    #endif
}


void MainWindowController::addNewRouteToCurrentProject(const QColor &newColor) {
    RouteData newRoute(newColor);
    currentProject->addRoute(newRoute);
    emit routeListChanged();
}

void MainWindowController::addNewNodeToRoute(int x, int y, const QColor &newColor, int routeIndex) {
    RouteNodeData newRouteNode(newColor);
    newRouteNode.setX(x);
    newRouteNode.setY(y);
    currentProject->addRouteNode(newRouteNode, routeIndex);
    emit routeNodeListChanged();
}

size_t MainWindowController::amountOfOpenProjects() {
    return openProjects.size();
}
