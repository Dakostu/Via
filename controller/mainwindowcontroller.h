#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../model/project.h"
#include <QObject>
#include <QUndoStack>
#include <QtPrintSupport/QPrinter>

class MainWindowController : public QObject
{
    Q_OBJECT

    QUndoStack undoCommandStack;
    std::unordered_map<QString, Project> openProjects;
    Project *currentProject;
    std::list<QString> recentlyOpenedProjects;
    static constexpr size_t MAX_LIST_SIZE = 10;

#ifndef QT_NO_PRINTER
    //QPrinter printer;
#endif


    void addFileToRecentlyOpenedProjects(const QString &fileName);

public:

    MainWindowController();

    Project* getCurrentProject();

public slots:

    void setCurrentProject(const QString &fileName);
    void saveCurrentProject();
    void saveCurrentProjectAs(const QString &fileName);
    void loadCurrentProjectFromFile(const QString &fileName);
    void printCurrentProject();
};

#endif // MAINWINDOWCONTROLLER_H
