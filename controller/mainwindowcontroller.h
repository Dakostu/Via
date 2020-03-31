#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../model/project.h"
#include "../controller/states/uistate.h"
#include "../controller/states/mainwindowstate.h"
#include "../controller/states/mapviewstate.h"
#include "../controller/states/routenodestate.h"
#include <memory>
#include <QObject>
#include <QStringListModel>
#include <QtPrintSupport/QPrinter>
#include <QUndoStack>
#include <type_traits>

namespace Via::Control {

class MainWindowController : public QObject
{
    Q_OBJECT

    static constexpr size_t MAX_LIST_SIZE = 10;
    static inline const char* PROGRAM_VER_KEY = "v";

    QUndoStack undoCommandStack;
    std::unordered_map<QString, Via::Model::Project> openProjects;
    Via::Model::Project *currentProject;
    std::list<QString> recentlyOpenedProjects;
    std::unique_ptr<MainWindowState> currentMainWindowState;
    std::unique_ptr<MapViewState> currentMapViewState;
    std::unique_ptr<RouteNodeState> currentRouteNodeState;
    QStringListModel currentRouteTitles;
    QStringListModel routeNodeTitles;
    void addFileToRecentlyOpenedProjects(const QString &fileName);

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

    void addNewRouteToCurrentProject(const QColor &newColor, char newStyle);
    void addNewNodeToRoute(int x, int y, const QColor &newColor, size_t routeIndex);
    size_t amountOfOpenProjects();
    void deleteRouteofCurrentProject(size_t index);
    void deleteNodeofRoute(size_t routeIndex, size_t nodeIndex);
    void swapCurrentProjectRoutes(size_t firstRoute, size_t secondRoute);
    void swapNodesOfRoute(size_t routeIndex, size_t firstNode, size_t secondNode);

    std::unique_ptr<MainWindowState>& getCurrentMainWindowState();
    std::unique_ptr<MapViewState>& getCurrentMapViewState();
    std::unique_ptr<RouteNodeState>& getCurrentRouteNodeState();


public slots:

    void addProject(const Via::Model::Project &project);
    void setCurrentProject(const QString &fileName);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);
    void setStyleOfCurrentRoute(size_t routeIndex, char newStyle);
    void setStyleOfCurrentRouteNode(size_t routeIndex, size_t nodeIndex, char newStyle, bool isDifferentNow);
    void setColorOfCurrentRoute(size_t routeIndex, const QColor &newColor);
    void setColorOfCurrentRouteNode(size_t routeIndex, size_t nodeIndex, const QColor &newColor, bool isDifferentNow);


signals:
    void currentProjectChanged();
    void routeListChanged();
    void routeNodeListChanged();

};

}

#endif // MAINWINDOWCONTROLLER_H
