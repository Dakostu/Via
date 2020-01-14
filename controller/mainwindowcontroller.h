#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QUndoStack>
#include <QtPrintSupport/QPrinter>

class MainWindowController : public QObject
{
    Q_OBJECT

    QUndoStack undoCommandStack;

#ifndef QT_NO_PRINTER
    //QPrinter printer;
#endif


public:

    MainWindowController();
};

#endif // MAINWINDOWCONTROLLER_H
