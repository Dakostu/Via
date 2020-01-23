#include "mainwindowcontroller.h"

MainWindowController::MainWindowController()
{

}


void MainWindowController::saveCurrentProject() {

    auto projectJSON = currentProject->toJSON();
    projectJSON["programVer"] = "1.0";

}

void MainWindowController::loadCurrentProjectFromFile(const QString &fileName) {

}

void MainWindowController::printCurrentProject() {
    #ifndef QT_NO_PRINTER


    #endif
}
