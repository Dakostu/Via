#include "uimovenodesstate.h"
#include "mainwindowcontroller.h"
#include "programversion.h"
#include "jsonfile.h"
#include "../interfaces/localizable.h"


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
}

QStringListModel& MainWindowController::getCurrentRoutesStringList() {
    QStringList currentRouteList;

    for (const auto &route : currentProject->getRoutes()) {
        currentRouteList << route.getName();
    }

    currentRoutes.setStringList(currentRouteList);
    return currentRoutes;
}

void MainWindowController::deleteRouteofCurrentProject(int index) {
    currentProject->deleteRoute(index);
}

void MainWindowController::printCurrentProject() {
    #ifndef QT_NO_PRINTER


    #endif
}


void MainWindowController::addNewRouteToCurrentProject(const QColor &newColor) {
    RouteData newRoute(newColor);
    currentProject->addRoute(newRoute);
}

size_t MainWindowController::amountOfOpenProjects() {
    return openProjects.size();
}
