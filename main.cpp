#include "ui/mainwindow.h"

#include "controller/mainwindowcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindowController controller;
    MainWindow w(nullptr, controller);
    w.show();
    return a.exec();
}
