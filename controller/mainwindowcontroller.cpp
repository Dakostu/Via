#include "../controller/states/mainwindowmovenodestate.h"
#include "../controller/states/mapviewmovenodestate.h"
#include "../controller/states/routenodemovenodestate.h"
#include "mainwindowcontroller.h"
#include "programversion.h"
#include "jsonfile.h"
#include "../ui/localizeduistrings.h"

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

void MainWindowController::updateStringListModel(QStringListModel &model, const IndexList<Nameable*> &nameables) {
    QStringList currentList;

    for (const auto &nameable : nameables) {
        currentList << nameable->getName();
    }

    model.setStringList(currentList);
}

Project* MainWindowController::getCurrentProject() {
    return currentProject;
}

void MainWindowController::setCurrentProject(const QString &fileName) {
    currentProject = &openProjects.at(fileName);
    emit currentProjectChanged();
}

QStringListModel& MainWindowController::getCurrentRouteTitles() {
    auto &routes = currentProject->getRoutes();
    IndexList<Nameable*> nameables;
    for (const auto route : routes) {
        nameables.emplace_back(route);
    }
    updateStringListModel(currentRouteTitles, nameables);
    return currentRouteTitles;
}

QStringListModel& MainWindowController::getNodeTitlesOfRoute(size_t index) {
    auto &routeNodes = (*currentProject->getRoutes()[index])->getNodes();
    IndexList<Nameable*> nameables;
    for (const auto routeNode : routeNodes) {
        nameables.emplace_back(routeNode);
    }
    updateStringListModel(currentRouteNodeTitles, nameables);
    return currentRouteNodeTitles;
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

void MainWindowController::addNewRouteToCurrentProject(Route &newRoute) {
    currentProject->addRoute(newRoute);
}

size_t MainWindowController::amountOfOpenProjects() {
    return openProjects.size();
}
