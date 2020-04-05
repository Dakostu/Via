#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../model/project.h"
#include "../controller/states/uistate.h"
#include "../controller/states/mainwindowstate.h"
#include "../controller/states/mapviewstate.h"
#include "../controller/states/routenodestate.h"
#include "../shapes/route.h"
#include <memory>
#include <QObject>
#include <QStringListModel>

namespace Via::Control {

class MainWindowController : public QObject
{
    Q_OBJECT

    static constexpr size_t MAX_LIST_SIZE = 10;
    static inline const char* PROGRAM_VER_KEY = "v";

    std::unordered_map<QString, Via::Model::Project> openProjects;
    Via::Model::Project *currentProject;
    std::list<QString> recentlyOpenedProjects;
    std::unique_ptr<MainWindowState> currentMainWindowState;
    std::unique_ptr<MapViewState> currentMapViewState;
    std::unique_ptr<RouteNodeState> currentRouteNodeState;
    QStringListModel currentRouteTitles;
    QStringListModel currentRouteNodeTitles;

    void addFileToRecentlyOpenedProjects(const QString &fileName);
    void updateStringListModel(QStringListModel &model, const Via::Structures::IndexList<Via::Interfaces::Nameable*> &nameables);

public:

    MainWindowController();

    Via::Model::Project* getCurrentProject();    
    QStringListModel& getCurrentRouteTitles();
    QStringListModel& getNodeTitlesOfRoute(size_t index);

    template <typename NewMainWindowState, typename NewMapViewState, typename NewRouteNodeState>
    void changeUIStates() {
        currentMainWindowState.reset(new NewMainWindowState);
        currentMapViewState.reset(new NewMapViewState);
        currentRouteNodeState.reset(new NewRouteNodeState);
    }

    void addNewRouteToCurrentProject(Via::Shapes::Route &newRoute);
    size_t amountOfOpenProjects();

    std::unique_ptr<MainWindowState>& getCurrentMainWindowState();
    std::unique_ptr<MapViewState>& getCurrentMapViewState();
    std::unique_ptr<RouteNodeState>& getCurrentRouteNodeState();

    Via::Shapes::Route& getRouteOfCurrentProject(size_t routeIndex);
    Via::Shapes::RouteNode& getRouteNodeofCurrentProject(size_t routeIndex, size_t routeNodeIndex);


public slots:

    void addProject(const Via::Model::Project &project);
    void setCurrentProject(const QString &fileName);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);


signals:
    void currentProjectChanged();

};

}

#endif // MAINWINDOWCONTROLLER_H
