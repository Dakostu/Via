#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../model/checkablestringlistmodel.h"
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

    std::unique_ptr<Via::Model::Project> currentProject;
    std::list<QString> recentlyOpenedProjects;
    std::unique_ptr<MainWindowState> currentMainWindowState;
    std::unique_ptr<MapViewState> currentMapViewState;
    std::unique_ptr<RouteNodeState> currentRouteNodeState;
    Via::Model::CheckableStringListModel currentRouteTitles;
    Via::Model::CheckableStringListModel currentRouteNodeTitles;

    void addFileToRecentlyOpenedProjects(const QString &fileName);
    void updateStringListModel(Via::Model::CheckableStringListModel &model,
                               const std::vector<Via::Interfaces::MapViewPlaceable*> &mapViewPlaceables);

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

    std::unique_ptr<MainWindowState>& getCurrentMainWindowState();
    std::unique_ptr<MapViewState>& getCurrentMapViewState();
    std::unique_ptr<RouteNodeState>& getCurrentRouteNodeState();

    Via::Shapes::Route& getRouteOfCurrentProject(size_t routeIndex);
    Via::Shapes::RouteNode& getRouteNodeofCurrentProject(size_t routeIndex, size_t routeNodeIndex);
    void swapRoutesOfCurrentProject(size_t firstRoute, size_t secondRoute);
    void deleteRoute(size_t routeIndex);
    void updateRouteNodeColor(size_t routeNodeIndex, const QColor &newColor);
    void updateRouteColor(size_t routeIndex, const QColor &newColor);

public slots:

    void setCurrentProject(Via::Model::Project *project);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);

signals:
    void currentProjectChanged();
    void needToChangeVisibilityOfRoute(int routeIndex, bool visible);
    void needToChangeVisibilityOfCurrentRouteNode(int routeNodeIndex, bool visible);

};

}

#endif // MAINWINDOWCONTROLLER_H
