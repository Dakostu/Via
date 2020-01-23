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
    std::list<Project> openProjects;
    Project *currentProject;
    std::list<QString> recentlyOpenedProjects;

#ifndef QT_NO_PRINTER
    //QPrinter printer;
#endif


public:

    MainWindowController();


public slots:

    void saveCurrentProject();
    void loadCurrentProjectFromFile(const QString &fileName);
    void printCurrentProject();
};

#endif // MAINWINDOWCONTROLLER_H
