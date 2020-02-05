#include "ui/mainwindow.h"

#include "controller/mainwindowcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Via::Control::MainWindowController controller;
    Via::UI::MainWindow w(nullptr, controller);
    w.show();
    return a.exec();
}
