#include "uimovenodesstate.h"
#include "mainwindowcontroller.h"
#include "programversion.h"
#include "jsonfile.h"

MainWindowController::MainWindowController()
    : currentState(new UIMoveNodesState)
{

}

void MainWindowController::saveCurrentProjectAs(const QString &fileName) {
    auto projectJSON = currentProject->toJSON();
    projectJSON["programVer"] = ProgramVersion::generateCurrentProgramVersion()();
    projectJSON["fileName"] = fileName;

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

UIState *MainWindowController::getCurrentState() const
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

void MainWindowController::printCurrentProject() {
    #ifndef QT_NO_PRINTER


    #endif
}
