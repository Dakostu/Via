#include "../../ui/mainwindow.h"
#include "mainwindowaddnodestate.h"

using namespace Via::Control;
using namespace Via::UI;

void MainWindowAddNodeState::setToggleButtons(MainWindow *window) {
    window->getQuickButtonAutoAdd()->setChecked(true);
    window->getQuickButtonMove()->setChecked(false);
    window->getQuickButtonSelect()->setChecked(false);
}
