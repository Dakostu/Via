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

#ifndef QT_NO_PRINTER
    //QPrinter printer;
#endif


    void addFileToRecentlyOpenedProjects(const QString &fileName);

public:

    MainWindowController();

    Via::Model::Project* getCurrentProject();    
    QStringListModel& getCurrentRouteTitles();
    QStringListModel& getNodeTitlesOfRoute(int index);

    template <typename NewMainWindowState, typename NewMapViewState, typename NewRouteNodeState>
    void changeUIStates() {
        currentMainWindowState.reset(new NewMainWindowState);
        currentMapViewState.reset(new NewMapViewState);
        currentRouteNodeState.reset(new NewRouteNodeState);
    }

    void addNewRouteToCurrentProject(const QColor &newColor, char newStyle);
    void addNewNodeToRoute(int x, int y, const QColor &newColor, int routeIndex);
    size_t amountOfOpenProjects();
    void deleteRouteofCurrentProject(int index);
    void deleteNodeofRoute(int routeIndex, int nodeIndex);
    void swapCurrentProjectRoutes(int x, int y);
    void swapNodesOfRoute(int routeIndex, int x, int y);

    std::unique_ptr<MainWindowState>& getCurrentMainWindowState();
    std::unique_ptr<MapViewState>& getCurrentMapViewState();
    std::unique_ptr<RouteNodeState>& getCurrentRouteNodeState();


public slots:

    void addProject(const Via::Model::Project &project);
    void setCurrentProject(const QString &fileName);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);
    void printCurrentProject();
    void setStyleOfCurrentRoute(int routeIndex, char newStyle);
    void setStyleOfCurrentRouteNode(int routeIndex, int nodeIndex, char newStyle, bool isDifferentNow);
    void setColorOfCurrentRoute(int routeIndex, const QColor &newColor);
    void setColorOfCurrentRouteNode(int routeIndex, int nodeIndex, const QColor &newColor, bool isDifferentNow);


signals:
    void currentProjectChanged();
    void routeListChanged();
    void routeNodeListChanged();

};

}

#endif // MAINWINDOWCONTROLLER_H
