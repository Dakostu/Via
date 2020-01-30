#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../model/project.h"
#include "../controller/uistate.h"
#include <memory>
#include <QObject>
#include <QStringListModel>
#include <QtPrintSupport/QPrinter>
#include <QUndoStack>

class MainWindowController : public QObject
{
    Q_OBJECT

    static constexpr size_t MAX_LIST_SIZE = 10;
    QUndoStack undoCommandStack;
    std::unordered_map<QString, Project> openProjects;
    Project *currentProject;
    std::list<QString> recentlyOpenedProjects;
    std::unique_ptr<UIState> currentState;
    QStringListModel currentRoutes;

#ifndef QT_NO_PRINTER
    //QPrinter printer;
#endif


    void addFileToRecentlyOpenedProjects(const QString &fileName);

public:

    MainWindowController();

    Project* getCurrentProject();
    std::unique_ptr<UIState>& getCurrentState();
    QStringListModel& getCurrentRoutesStringList();

    template <typename State>
    void changeUIState() {
        currentState.reset(new State);
    }

    void addNewRouteToCurrentProject(const QColor &newColor);
    size_t amountOfOpenProjects();
    void deleteRouteofCurrentProject(int index);
    void swapCurrentProjectRoutes(int x, int y);


public slots:

    void addProject(const Project &project);
    void setCurrentProject(const QString &fileName);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);
    void printCurrentProject();


signals:
    void currentProjectChanged();
    void routeListChanged();



};

#endif // MAINWINDOWCONTROLLER_H
