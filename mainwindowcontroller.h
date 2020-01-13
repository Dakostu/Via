#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QUndoStack>

class MainWindowController : public QObject
{
    Q_OBJECT

    QUndoStack undoCommandStack;
    QWidget *ui;

public:

    MainWindowController(QWidget *parent);
};

#endif // MAINWINDOWCONTROLLER_H
