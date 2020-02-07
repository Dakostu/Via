#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../model/project.h"
#include "../controller/states/uistate.h"
#include <memory>
#include <QObject>
#include <QStringListModel>
#include <QtPrintSupport/QPrinter>
#include <QUndoStack>

namespace Via::Control {

class MainWindowController : public QObject
{
    Q_OBJECT

    static constexpr size_t MAX_LIST_SIZE = 10;
    QUndoStack undoCommandStack;
    std::unordered_map<QString, Via::Model::Project> openProjects;
    Via::Model::Project *currentProject;
    std::list<QString> recentlyOpenedProjects;
    std::unique_ptr<UIState> currentState;
    QStringListModel currentRouteTitles;
    QStringListModel routeNodeTitles;

#ifndef QT_NO_PRINTER
    //QPrinter printer;
#endif


    void addFileToRecentlyOpenedProjects(const QString &fileName);

public:

    MainWindowController();

    Via::Model::Project* getCurrentProject();
    std::unique_ptr<UIState>& getCurrentState();
    QStringListModel& getCurrentRouteTitles();
    QStringListModel& getNodeTitlesOfRoute(int index);

    template <typename State>
    void changeUIState() {
        currentState.reset(new State);
    }

    void addNewRouteToCurrentProject(const QColor &newColor);
    void addNewNodeToRoute(int x, int y, const QColor &newColor, int routeIndex);
    size_t amountOfOpenProjects();
    void deleteRouteofCurrentProject(int index);
    void deleteNodeofRoute(int routeIndex, int nodeIndex);
    void swapCurrentProjectRoutes(int x, int y);
    void swapNodesOfRoute(int routeIndex, int x, int y);


public slots:

    void addProject(const Via::Model::Project &project);
    void setCurrentProject(const QString &fileName);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);
    void printCurrentProject();


signals:
    void currentProjectChanged();
    void routeListChanged();
    void routeNodeListChanged();

};

}

#endif // MAINWINDOWCONTROLLER_H
