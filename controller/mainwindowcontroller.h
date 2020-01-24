#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../model/project.h"
#include "../controller/uistate.h"
#include <memory>
#include <QObject>
#include <QUndoStack>
#include <QtPrintSupport/QPrinter>

class MainWindowController : public QObject
{
    Q_OBJECT

    static constexpr size_t MAX_LIST_SIZE = 10;
    QUndoStack undoCommandStack;
    std::unordered_map<QString, Project> openProjects;
    Project *currentProject;
    std::list<QString> recentlyOpenedProjects;
    std::unique_ptr<UIState> currentState;

#ifndef QT_NO_PRINTER
    //QPrinter printer;
#endif


    void addFileToRecentlyOpenedProjects(const QString &fileName);

public:

    MainWindowController();

    Project* getCurrentProject();

    std::unique_ptr<UIState>& getCurrentState();

    template <typename State>
    void changeUIState() {
        currentState.reset(new State);
    }

public slots:

    void setCurrentProject(const QString &fileName);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);
    void printCurrentProject();

};

#endif // MAINWINDOWCONTROLLER_H
